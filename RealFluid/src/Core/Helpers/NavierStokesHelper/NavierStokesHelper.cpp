#include "NavierStokesHelper.h"

void Helpers::AdjustSolidCellConditions(Grid* grid, FluidCell* cell)
{
    if (cell->Type != Solid)
        return;

    int i, j, k;
    auto index = grid->GetCellIndex(cell->X, cell->Y, cell->Z);
    i = index[0];
    j = index[1];
    k = index[2];

    auto t = grid->GetCellAtIndex(i, j + 1, k);
    auto r = grid->GetCellAtIndex(i + 1, j, k);
    auto l = grid->GetCellAtIndex(i - 1, j, k);

    float totalPressure = 0.0;
    float totalU = 0.0;
    float totalV = 0.0;

    if (t != nullptr && t->Type != Solid)
    {
        totalPressure += t->Pressure;
        totalU += -(t->U);
    }
    if (l != nullptr && l->Type != Solid)
    {
        totalV += -(l->V);
    }
    if (r != nullptr && r->Type != Solid)
    {
        totalV += -(r->V);
    }

    cell->U = totalU;
    cell->V = totalV;
    cell->W = 0.0;

    cell->Pressure = totalPressure;
}
