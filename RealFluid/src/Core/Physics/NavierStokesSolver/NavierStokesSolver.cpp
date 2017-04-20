#include "NavierStokesSolver.h"

#include <Core/Helpers/NavierStokesHelper/NavierStokesHelper.h>
#include <Core/Helpers/GridHelper/GridHelper.h>

auto dt = 1.0 / 20.0;
auto viscosity = 0.0001;
vector<float> gravity = { 0.0f, -9.8f, 0.0f };

auto particlesAdded = 0;

/* Public */
void ProcessGrid(Grid* grid)
{
    if (particlesAdded < 120)
    {
        particlesAdded++;

        if (particlesAdded % 4 == 0)
            AddParticles(grid);
    }

    // Update cell types based on particles
    UpdateCellsWithParticles(grid);

    // Adjust boundary conditions for solid / surface cells
    AdjustBoundaryConditions(grid);

    // Update velocities for cells
    UpdateNewVelocities(grid);

    // Pressure iteration
    AdjustForIncompressibility(grid);

    // Update position of particles
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
    auto cells = *(grid->GetCellsVector());

    double dx, dy, dz;
    double dx2, dy2, dz2;

    dx = dy = dz = grid->GetCellDimensions();
    dx2 = pow(dx, 2);
    dy2 = pow(dy, 2);
    dz2 = pow(dz, 2);

    double v_dx2, v_dy2, v_dz2;
    v_dx2 = viscosity / dx2;
    v_dy2 = viscosity / dy2;
    v_dz2 = viscosity / dz2;

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

        auto emptyGrav = cell->Type == Empty ? 1.0 : 1.0;

        float new_u =
            grid->GetCellU(i, j, k) +
            dt *
            (
            ((1.0 / dx) * (pow(grid->GetCellAverageU(i, j, k), 2) - pow(grid->GetCellAverageU(i + 1, j, k), 2))) +
                ((1.0 / dy) * (grid->GetCellUV(i, j - 1, k) - grid->GetCellUV(i, j, k))) +
                ((1.0 / dz) * (grid->GetCellWU(i, j, k - 1) - grid->GetCellWU(i, j, k))) +
                (gravity[0] * emptyGrav) +
                ((1.0 / dx) * (grid->GetCellPressure(i, j, k) - grid->GetCellPressure(i + 1, j, k))) +
                (v_dx2 * (grid->GetCellU(i + 1, j, k) - (2 * grid->GetCellU(i, j, k)) + grid->GetCellU(i - 1, j, k))) +
                (v_dy2 * (grid->GetCellU(i, j + 1, k) - (2 * grid->GetCellU(i, j, k)) + grid->GetCellU(i, j - 1, k))) +
                (v_dz2 * (grid->GetCellU(i, j, k + 1) - (2 * grid->GetCellU(i, j, k)) + grid->GetCellU(i, j, k - 1)))
                );

        float new_v =
            grid->GetCellV(i, j, k) +
            dt *
            (
            ((1 / dx) * (grid->GetCellUV(i - 1, j, k) - grid->GetCellUV(i, j, k))) +
                ((1.0 / dy) * (pow(grid->GetCellAverageV(i, j, k), 2) - pow(grid->GetCellAverageV(i, j + 1, k), 2))) +
                ((1.0 / dz) * (grid->GetCellVW(i, j, k - 1) - grid->GetCellVW(i, j, k))) +
                (gravity[1] * emptyGrav) +
                ((1.0 / dy) * (grid->GetCellPressure(i, j, k) - grid->GetCellPressure(i, j + 1, k))) +
                (v_dx2 * (grid->GetCellV(i + 1, j, k) - 2 * grid->GetCellV(i, j, k) + grid->GetCellV(i - 1, j, k))) +
                (v_dy2 * (grid->GetCellV(i, j + 1, k) - 2 * grid->GetCellV(i, j, k) + grid->GetCellV(i, j - 1, k))) +
                (v_dz2 * (grid->GetCellV(i, j, k + 1) - 2 * grid->GetCellV(i, j, k) + grid->GetCellV(i, j, k - 1)))
                );

        float new_w =
            grid->GetCellW(i, j, k) +
            dt *
            (
            ((1.0 / dx) * (grid->GetCellWU(i - 1, j, k) - grid->GetCellWU(i, j, k))) +
                ((1.0 / dy) * (grid->GetCellVW(i, j - 1, k) - grid->GetCellVW(i, j, k))) +
                ((1.0 / dz) * (pow(grid->GetCellAverageW(i, j, k), 2) - pow(grid->GetCellAverageW(i, j, k + 1), 2))) +
                (gravity[2] * emptyGrav) +
                ((1.0 / dz) * (grid->GetCellPressure(i, j, k) - grid->GetCellPressure(i, j, k + 1))) +
                (v_dx2 * (grid->GetCellW(i + 1, j, k) - 2 * grid->GetCellW(i, j, k) + grid->GetCellW(i - 1, j, k))) +
                (v_dy2 * (grid->GetCellW(i, j + 1, k) - 2 * grid->GetCellW(i, j, k) + grid->GetCellW(i, j - 1, k))) +
                (v_dz2 * (grid->GetCellW(i, j, k + 1) - 2 * grid->GetCellW(i, j, k) + grid->GetCellW(i, j, k - 1)))
                );

        // Update the values into the buffer to later replace the grid with
        struct UpdatedCellValues newValues;
        newValues.I = i;
        newValues.J = j;
        newValues.K = k;
        newValues.U = new_u;
        newValues.V = new_v;
        newValues.W = new_w;

        UpdatedCellVectorBuffer.push_back(newValues);
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
    double dx, dy, dz;
    double dx2, dy2, dz2;

    dx = dy = dz = grid->GetCellDimensions();
    dx2 = pow(dx, 2);
    dy2 = pow(dy, 2);
    dz2 = pow(dz, 2);

    float betaDenom = (2.0 * dt) * ((1.0 / dx2) + (1.0 / dy2) + (1.0 / dz2));
    float B = BETA_0 / betaDenom;

    auto cells = *(grid->GetCellsVector());

    for (auto iters = 0; iters < 3; iters++)
    {
        #pragma omp parallel for
        for (auto c = 0; c < cells.size(); c++)
        {
            auto cell = cells[c];

            if (cell->Boundary == Inflow)
                continue;

            int i, j, k;
            float du, dv, dw;

            float Dx, Dy, Dz;
            float D, dp;

            auto index = grid->GetCellIndex(cell->X, cell->Y, cell->Z);
            i = index[0];
            j = index[1];
            k = index[2];

            // Divergence
            Dx = (1.0 / dx) * (grid->GetCellU(i, j, k) - grid->GetCellU(i - 1, j, k));
            Dy = (1.0 / dy) * (grid->GetCellV(i, j, k) - grid->GetCellV(i, j - 1, k));
            Dz = (1.0 / dz) * (grid->GetCellW(i, j, k) - grid->GetCellW(i, j, k - 1));

            D = -(Dx + Dy + Dz);

            // Pressure
            dp = B * D;

            // Change in velocity due to pressure
            du = (dt / dx) * dp;
            dv = (dt / dy) * dp;
            dw = (dt / dz) * dp;

            /*
            // Update next cells
            auto prev_x = grid->GetCellAtIndex(i - 1, j, k);
            auto prev_y = grid->GetCellAtIndex(i, j - 1, k);
            auto prev_z = grid->GetCellAtIndex(i, j, k - 1);
            if (prev_x != nullptr)
                prev_x->U -= du;
            if (prev_y != nullptr)
                prev_y->V -= dv;
            if (prev_z != nullptr)
                prev_z->W -= dw;
            //*/


            struct UpdatedCellValues newValues;
            newValues.I = i;
            newValues.J = j;
            newValues.K = k;
            newValues.U = cell->U + du;
            newValues.V = cell->V + dv;
            newValues.W = cell->W + dw;
            newValues.Pressure = cell->Pressure + dp;

            UpdatedCellVectorBuffer.push_back(newValues);
        }

        #pragma omp parallel for
        for (auto c = 0; c < UpdatedCellVectorBuffer.size(); c++)
        {
            auto update = UpdatedCellVectorBuffer[c];

            auto cell = grid->GetCellAtIndex(update.I, update.J, update.K);
            cell->U = update.U;
            cell->V = update.V;
            cell->W = update.W;
            cell->Pressure = update.Pressure;
        }

        UpdatedCellVectorBuffer.clear();
    }
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

    //    #pragma omp parallel for
    for (auto p = 0; p < particles.size(); p++)
    {
        auto particle = particles[p];

        auto velocity = Helpers::ComputeParticleVelocity(grid, particle);

        particle->MoveBy(dt * velocity.U, dt * velocity.V, dt * velocity.W);
    }
}
