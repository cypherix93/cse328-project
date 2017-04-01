#pragma once
#include <GL/glew.h>

#include "Core/Fluid/Grid/Grid.h"
#include "Core/Fluid/Cell/FluidCell.h"

/* Public */
void DrawCellGrid(Grid grid);

/* Private */
static void DrawCell(FluidCell cell);
