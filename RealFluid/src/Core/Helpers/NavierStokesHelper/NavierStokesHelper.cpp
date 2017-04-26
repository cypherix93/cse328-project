#include "NavierStokesHelper.h"

struct UpdatedCellValues Helpers::AdjustSolidCellConditions(Grid* grid, FluidCell* cell)
{
    int i, j, k;
    i = cell->I;
    j = cell->J;
    k = cell->K;

    auto t = grid->GetCellAtIndex(i, j + 1, k);
    auto r = grid->GetCellAtIndex(i + 1, j, k);
    auto l = grid->GetCellAtIndex(i - 1, j, k);

    float totalPressure = 0.0;
    float totalU = 0.0;
    float totalV = 0.0;

    if (t != nullptr && t->Type != Solid)
    {
        totalPressure += t->Pressure;
        //totalU += -(t->U);
    }
    if (l != nullptr && l->Type != Solid)
    {
        totalV += -(l->V);
    }
    if (r != nullptr && r->Type != Solid)
    {
        totalV += -(r->V);
    }

    struct UpdatedCellValues newValues;
    newValues.I = i;
    newValues.J = j;
    newValues.K = k;
    newValues.U = totalU;
    newValues.V = totalV;
    newValues.W = 0.0;
    newValues.Pressure = totalPressure;

    return newValues;
}

UpdatedCellValues Helpers::AdjustSurfaceCellConditions(Grid* grid, FluidCell* cell)
{
    int i, j, k;
    i = cell->I;
    j = cell->J;
    k = cell->K;

    auto t = grid->GetCellAtIndex(i, j + 1, k);
    auto r = grid->GetCellAtIndex(i + 1, j, k);
    auto b = grid->GetCellAtIndex(i, j - 1, k);
    auto l = grid->GetCellAtIndex(i - 1, j, k);

    float totalPressure = 0.0;
    float totalU = 0.0;
    float totalV = 0.0;

    // Set U vector
    if (r != nullptr && r->Type == Empty)
    {
        if (l != nullptr && l->IsFluid())
        {
            totalU = l->U;
        }
    }
    if (l != nullptr && l->Type == Empty)
    {
        if (r != nullptr && r->IsFluid())
        {
            totalU = r->U;
        }
    }

    // Set V vector
    if (t != nullptr && t->Type == Empty)
    {
        if (b != nullptr && b->IsFluid())
        {
            totalV = b->V;
        }
    }
    if (b != nullptr && b->Type == Empty)
    {
        if (t != nullptr && t->IsFluid())
        {
            totalV = t->V;
        }
    }

    struct UpdatedCellValues newValues;
    newValues.I = i;
    newValues.J = j;
    newValues.K = k;
    newValues.U = totalU;
    newValues.V = totalV;
    newValues.W = 0.0;
    newValues.Pressure = totalPressure;

    return newValues;
}
