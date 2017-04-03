#include "NavierStokesSolver.h"

float dt = 10.0;

/* Public */
void ProcessGrid(Grid* grid)
{
}

/* Private */
void AdjustForIncompressibility(Grid* grid)
{
    float D, B, dp;

    auto needsReprocessing = false;

    auto cells = grid->GetCells();

    for (auto &pair : *cells)
    {
        auto cell = &(pair.second);

        D = ComputeDivergence(cell);
        B = ComputeBeta(cell);

        dp = ComputeDeltaPressure(B, D);

        cell->U += (dt / cell->Width) * dp;
        cell->V += (dt / cell->Height) * dp;
        cell->W += (dt / cell->Depth) * dp;

        cell->Pressure += dp;

        if (abs(D) > MIN_DIVERGENCE)
            needsReprocessing = true;
    }
    //
    //    if (needsReprocessing)
    //        ProcessGrid(grid);
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
