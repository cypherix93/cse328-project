#include "NavierStokesSolver.h"

auto dt = 1.0 / 20.0;
auto viscosity = 0.0001;
vector<float> gravity = { 0.0f, -9.8f, 0.0f };

auto particlesAdded = 0;

/* Public */
void ProcessGrid(Grid* grid)
{
    if (particlesAdded < 40)
    {
        particlesAdded++;

        if (particlesAdded % 4 == 0)
            AddParticles(grid);
    }
    UpdateCellsWithParticles(grid);

    AdjustBoundaryConditions(grid);
    UpdateNewVelocities(grid);
    AdjustForIncompressibility(grid);

    MoveParticles(grid);
}

void UpdateNewVelocities(Grid* grid)
{
    ComputeNewVelocities(grid);

    #pragma omp parallel for
    for (auto c = 0; c < UpdatedCellVectorBuffer.size(); c++)
    {
        auto update = UpdatedCellVectorBuffer[c];

        auto cell = grid->GetCellAtIndex(update.I, update.J, update.K);
        cell->U = update.U;
        cell->V = update.V;
        cell->W = update.W;
    }

    UpdatedCellVectorBuffer.clear();
}

void ComputeNewVelocities(Grid* grid)
{
    double dx, dy, dz;
    double dx2, dy2, dz2;

    auto cells = *(grid->GetCellsVector());

    #pragma omp parallel for
    for (auto c = 0; c < cells.size(); c++)
    {
        auto cell = cells[c];

        if (cell->Boundary == Inflow)
            continue;

        int i, j, k;
        auto index = grid->GetCellIndex(cell->X, cell->Y, cell->Z);
        i = index[0];
        j = index[1];
        k = index[2];

        dx = cell->Width;
        dy = cell->Height;
        dz = cell->Depth;

        dx2 = pow(dx, 2);
        dy2 = pow(dy, 2);
        dz2 = pow(dz, 2);

        auto emptyGrav = cell->Type == Empty ? 1.0 : 1.0;

        float new_u =
            grid->get_u_plus(i, j, k) +
            dt *
            (
            ((1.0 / dx) * (pow(grid->get_u_avg(i, j, k), 2) - pow(grid->get_u_avg(i + 1, j, k), 2))) +
                ((1.0 / dy) * (grid->get_uv_plus(i, j - 1, k) - grid->get_uv_plus(i, j, k))) +
                ((1.0 / dz) * (grid->get_uw_plus(i, j, k - 1) - grid->get_uw_plus(i, j, k))) +
                (gravity[0] * emptyGrav) +
                ((1.0 / dx) * (grid->getPressure(i, j, k) - grid->getPressure(i + 1, j, k))) +
                ((viscosity / dx2) * (grid->get_u_plus(i + 1, j, k) - 2 * grid->get_u_plus(i, j, k) + grid->get_u_plus(i - 1, j, k))) +
                ((viscosity / dy2) * (grid->get_u_plus(i, j + 1, k) - 2 * grid->get_u_plus(i, j, k) + grid->get_u_plus(i, j - 1, k))) +
                ((viscosity / dz2) * (grid->get_u_plus(i, j, k + 1) - 2 * grid->get_u_plus(i, j, k) + grid->get_u_plus(i, j, k - 1)))
                );

        float new_v =
            grid->get_v_plus(i, j, k) +
            dt *
            (
            ((1 / dx) * (grid->get_uv_plus(i - 1, j, k) - grid->get_uv_plus(i, j, k))) +
                ((1.0 / dy) * (pow(grid->get_v_avg(i, j, k), 2) - pow(grid->get_v_avg(i, j + 1, k), 2))) +
                ((1.0 / dz) * (grid->get_vw_plus(i, j, k - 1) - grid->get_vw_plus(i, j, k))) +
                (gravity[1] * emptyGrav) +
                ((1.0 / dy) * (grid->getPressure(i, j, k) - grid->getPressure(i, j + 1, k))) +
                ((viscosity / dx2) * (grid->get_v_plus(i + 1, j, k) - 2 * grid->get_v_plus(i, j, k) + grid->get_v_plus(i - 1, j, k))) +
                ((viscosity / dy2) * (grid->get_v_plus(i, j + 1, k) - 2 * grid->get_v_plus(i, j, k) + grid->get_v_plus(i, j - 1, k))) +
                ((viscosity / dz2) * (grid->get_v_plus(i, j, k + 1) - 2 * grid->get_v_plus(i, j, k) + grid->get_v_plus(i, j, k - 1)))
                );

        float new_w =
            grid->get_w_plus(i, j, k) +
            dt *
            (
            ((1.0 / dx) * (grid->get_uw_plus(i - 1, j, k) - grid->get_uw_plus(i, j, k))) +
                ((1.0 / dy) * (grid->get_vw_plus(i, j - 1, k) - grid->get_vw_plus(i, j, k))) +
                ((1.0 / dz) * (pow(grid->get_w_avg(i, j, k), 2) - pow(grid->get_w_avg(i, j, k + 1), 2))) +
                (gravity[2] * emptyGrav) +
                ((1.0 / dz) * (grid->getPressure(i, j, k) - grid->getPressure(i, j, k + 1))) +
                ((viscosity / dx2) * (grid->get_w_plus(i + 1, j, k) - 2 * grid->get_w_plus(i, j, k) + grid->get_w_plus(i - 1, j, k))) +
                ((viscosity / dy2) * (grid->get_w_plus(i, j + 1, k) - 2 * grid->get_w_plus(i, j, k) + grid->get_w_plus(i, j - 1, k))) +
                ((viscosity / dz2) * (grid->get_w_plus(i, j, k + 1) - 2 * grid->get_w_plus(i, j, k) + grid->get_w_plus(i, j, k - 1)))
                );

        // Update the values into the buffer to later replace the grid with
        struct UpdatedCellVector newVector;
        newVector.I = i;
        newVector.J = j;
        newVector.K = k;
        newVector.U = new_u;
        newVector.V = new_v;
        newVector.W = new_w;

        UpdatedCellVectorBuffer.push_back(newVector);
    }
}

/* Private */
void AdjustBoundaryConditions(Grid* grid)
{
    auto cells = *(grid->GetCellsVector());

    #pragma omp parallel for
    for (auto c = 0; c < cells.size(); c++)
    {
        auto cell = cells[c];

        Helpers::AdjustSolidCellConditions(grid, cell);
    }
}

void AdjustForIncompressibility(Grid* grid)
{
    float D, B, dp;

    auto iters = 0;
    auto needsReprocessing = false;

    auto cells = *(grid->GetCellsVector());

    do
    {
        iters++;

        #pragma omp parallel for
        for (auto c = 0; c < cells.size(); c++)
        {
            auto cell = cells[c];

            D = ComputeDivergence(cell);
            B = ComputeBeta(cell);

            dp = ComputeDeltaPressure(B, D);

            cell->U += (dt / cell->Width) * dp;
            cell->V += (dt / cell->Height) * dp;
            cell->W += (dt / cell->Depth) * dp;

            cell->Pressure += dp;

            needsReprocessing = (iters < 3) && (abs(D) > EPSILON);
        }
    } while (needsReprocessing);
}

void AddParticles(Grid* grid)
{
    auto cells = *(grid->GetCellsVector());

    #pragma omp parallel for
    for (auto c = 0; c < cells.size(); c++)
    {
        auto cell = cells[c];

        if (cell->Boundary == Inflow)
        {
            grid->AddParticle(cell);
        }
    }
}

void UpdateCellsWithParticles(Grid* grid)
{
    auto particles = *(grid->GetParticlesVector());

    auto cells = *(grid->GetCellsVector());

    int i, j, k;

    #pragma omp parallel for
    for (auto c = 0; c < cells.size(); c++)
    {
        auto cell = cells[c];

        // First see if any particles are in this cell
        auto isFull = false;

        #pragma omp parallel for
        for (auto p = 0; p < particles.size(); p++)
        {
            auto particle = particles[p];

            auto particleCell = grid->GetCellAtPixel(particle->X, particle->Y, particle->Z);

            if (particleCell == cell)
                isFull = true;
        }

        if (cell->Type != Solid)
            cell->Type = isFull ? Full : Empty;

        // If cell was deemed full, determine if it is a surface
        if (cell->Type != Full)
            continue;

        auto index = grid->GetCellIndex(cell->X, cell->Y, cell->Z);
        i = index[0];
        j = index[1];
        k = index[2];

        auto neighbors = {
            grid->GetCellAtIndex(i, j + 1, k),
            grid->GetCellAtIndex(i + 1, j, k),
            grid->GetCellAtIndex(i, j - 1, k),
            grid->GetCellAtIndex(i - 1, j, k),
        };

        for (auto neighbor : neighbors)
        {
            if (neighbor != nullptr && neighbor->Type == Empty)
            {
                cell->Type = Surface;
                break;
            }
        }
    }
}

void MoveParticles(Grid* grid)
{
    auto particles = *(grid->GetParticlesVector());

    #pragma omp parallel for
    for (auto p = 0; p < particles.size(); p++)
    {
        auto particle = particles[p];

        auto cell = grid->GetCellAtPixel(particle->X, particle->Y, particle->Z);

        if (cell != nullptr)
            particle->MoveBy(cell->U * dt, cell->V * dt, cell->W * dt);
    }
}

float ComputeDivergence(FluidCell* cell)
{
    auto Dx = (1.0 / cell->Width) * cell->U;
    auto Dy = (1.0 / cell->Height) * cell->V;
    auto Dz = (1.0 / cell->Depth) * cell->W;

    return -(Dx + Dy + Dz);
}

float ComputeBeta(FluidCell* cell)
{
    auto i_dx2 = 1 / pow(cell->Width, 2);
    auto i_dy2 = 1 / pow(cell->Height, 2);
    auto i_dz2 = 1 / pow(cell->Depth, 2);

    auto denom = (2 * dt) / (i_dx2 + i_dy2 + i_dz2);

    return BETA_0 / denom;
}

float ComputeDeltaPressure(float beta, float divergence)
{
    return beta * divergence;
}

