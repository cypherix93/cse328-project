#pragma once
#include <Core/Fluid/Cell/FluidCell.h>
#include <Core/Fluid/Grid/Grid.h>
#include <Core/Physics/NavierStokesSolver/NavierStokesSolver.h>

namespace Helpers
{
    struct UpdatedCellValues AdjustSolidCellConditions(Grid* grid, FluidCell* cell);
    struct UpdatedCellValues AdjustSurfaceCellConditions(Grid* grid, FluidCell* cell);
    struct UpdatedCellValues AdjustEmptyCellConditions(Grid* grid, FluidCell* cell);
    struct UpdatedCellValues AdjustSolidTouchingCellConditions(Grid* grid, FluidCell* cell);
}
