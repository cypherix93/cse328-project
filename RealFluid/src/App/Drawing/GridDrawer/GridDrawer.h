#pragma once
#include <GL/glew.h>

#include "Core/Fluid/Grid/Grid.h"
#include "Core/Fluid/Cell/FluidCell.h"

class GridDrawOptions
{
    public:
    GridDrawOptions();
    ~GridDrawOptions();

    bool DrawCellOutline;
    bool DrawCellContents;
    bool DrawCellVectors;
};


/* Public */
void DrawCellGrid(Grid grid, GridDrawOptions* options = nullptr);

/* Private */
static void DrawCell(FluidCell cell, bool drawContents, bool drawOutline, bool drawVectors);