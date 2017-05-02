#include "NavierStokesHelper.h"
#include <Core/Physics/Models/Environment.h>

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

    float totalU = 0.0;
    float totalV = 0.0;

    // Set U vector
    if (r != nullptr && r->Type == Empty)
    {
        if (l != nullptr && l->IsFluid())
        {
            totalU += l->U - (DT * grid->GetCellAverageV(i, j, k));
        }
    }
    if (l != nullptr && l->Type == Empty)
    {
        if (r != nullptr && r->IsFluid())
        {
            totalU += r->U - (DT * grid->GetCellAverageV(i, j, k));
        }
    }

    // Set V vector
    if (t != nullptr && t->Type == Empty)
    {
        if (b != nullptr && b->IsFluid())
        {
            totalV += b->V - (DT * grid->GetCellAverageU(i, j, k));
        }
    }
    if (b != nullptr && b->Type == Empty)
    {
        if (t != nullptr && t->IsFluid())
        {
            totalV += t->V - (DT * grid->GetCellAverageU(i, j, k));
        }
    }

    if ((r != nullptr && r->Type == Empty) && (l != nullptr && l->Type == Empty))
    {
        //totalU += GRAVITY.U;
    }
    if ((t != nullptr && t->Type == Empty) && (b != nullptr && b->Type == Empty))
    {
        //totalV += GRAVITY.V;
    }

    struct UpdatedCellValues newValues;
    newValues.I = i;
    newValues.J = j;
    newValues.K = k;
    newValues.U = cell->U + DT*(totalU + GRAVITY.U);
    newValues.V = cell->V + DT*(totalV + GRAVITY.V);
    newValues.W = 0.0;
    newValues.Pressure = ATM_PRESSURE;

    return newValues;
}

UpdatedCellValues Helpers::AdjustEmptyCellConditions(Grid* grid, FluidCell* cell)
{
    int i, j, k;
    i = cell->I;
    j = cell->J;
    k = cell->K;

    auto t = grid->GetCellAtIndex(i, j + 1, k);
    auto r = grid->GetCellAtIndex(i + 1, j, k);
    auto b = grid->GetCellAtIndex(i, j - 1, k);
    auto l = grid->GetCellAtIndex(i - 1, j, k);

    float totalU = 0.0;
    float totalV = 0.0;

    // Set U vector
    if (r != nullptr && r->Type == Surface)
    {
        totalU += r->U;
    }
    if (l != nullptr && l->Type == Surface)
    {
        totalU += l->U;
    }

    // Set V vector
    if (t != nullptr && t->Type == Surface)
    {
        totalV += t->V;
    }
    if (b != nullptr && b->Type == Surface)
    {
        totalV += b->V;
    }

    struct UpdatedCellValues newValues;
    newValues.I = i;
    newValues.J = j;
    newValues.K = k;
    newValues.U = totalU;
    newValues.V = totalV;
    newValues.W = 0.0;
    newValues.Pressure = cell->Pressure;

    return newValues;
}

UpdatedCellValues Helpers::AdjustSolidTouchingCellConditions(Grid* grid, FluidCell* cell)
{
    int i, j, k;
    i = cell->I;
    j = cell->J;
    k = cell->K;

    auto t = grid->GetCellAtIndex(i, j + 1, k);
    auto r = grid->GetCellAtIndex(i + 1, j, k);
    auto b = grid->GetCellAtIndex(i, j - 1, k);
    auto l = grid->GetCellAtIndex(i - 1, j, k);

    float totalU = cell->U;
    float totalV = cell->V;

    // Set U vector
    if (r != nullptr && r->IsSolid() && cell->U > 0)
    {
        totalU = 0.0;
    }
    if (l != nullptr && l->IsSolid() && cell->U < 0)
    {
        totalU = 0.0;
    }

    // Set V vector
    if (t != nullptr && t->IsSolid() && cell->V > 0)
    {
        totalV = 0.0;
    }
    if (b != nullptr && b->IsSolid() && cell->V < 0)
    {
        totalV = 0.0;
    }

    struct UpdatedCellValues newValues;
    newValues.I = i;
    newValues.J = j;
    newValues.K = k;
    newValues.U = totalU;
    newValues.V = totalV;
    newValues.W = 0.0;
    newValues.Pressure = cell->Pressure;

    return newValues;
}
