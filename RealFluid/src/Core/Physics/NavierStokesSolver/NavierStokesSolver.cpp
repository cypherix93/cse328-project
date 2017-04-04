#include "NavierStokesSolver.h"

auto dt = 1.0 / 10.0;
auto viscosity = 10.0;
vector<float> gravity = { 0.0f, -9.8f, 0.0f };

/* Public */
void ProcessGrid(Grid* grid)
{

    UpdateNewVelocities(grid);
    AdjustForIncompressibility(grid);
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

        float new_u =
            grid->get_u_plus(i, j, k) +
            dt *
            (
            ((1.0 / dx) * (pow(grid->get_u_avg(i, j, k), 2) - pow(grid->get_u_avg(i + 1, j, k), 2))) +
                ((1.0 / dy) * (grid->get_uv_plus(i, j - 1, k) - grid->get_uv_plus(i, j, k))) +
                ((1.0 / dz) * (grid->get_uw_plus(i, j, k - 1) - grid->get_uw_plus(i, j, k))) +
                gravity[0] +
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
                gravity[1] +
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
                gravity[2] +
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
void AdjustBoundaryConditios(Grid* grid)
{

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

