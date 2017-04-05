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
    bool DrawParticles;
};


/* Public */
void DrawCellGrid(Grid* grid, GridDrawOptions* options = nullptr);

/* Private */
static void DrawCell(FluidCell* cell, GridDrawOptions* options);
static void DrawParticle(Particle* particle);