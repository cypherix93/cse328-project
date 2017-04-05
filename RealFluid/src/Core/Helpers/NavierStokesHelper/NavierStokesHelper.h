#pragma once
#include <Core/Fluid/Cell/FluidCell.h>
#include <Core/Fluid/Grid/Grid.h>

namespace Helpers
{
    void AdjustSolidCellConditions(Grid* grid, FluidCell* cell);
}
