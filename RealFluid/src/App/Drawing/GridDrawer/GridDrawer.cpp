#include "GridDrawer.h"

GridDrawOptions::GridDrawOptions()
{
    CellDimensions = 40;

    DrawCellContents = true;
    DrawCellOutline = true;
    DrawCellVectors = true;
    DrawParticles = true;
}

GridDrawOptions::~GridDrawOptions()
{
}

void DrawCellGrid(Grid* grid, GridDrawOptions* options)
{
    if (options == nullptr)
        options = new GridDrawOptions();

    if (options->DrawParticles)
    {
        auto particles = grid->GetParticlesVector();

        for (auto &particle : *particles)
        {
            DrawParticle(particle, options);
        }
    }

    auto cells = grid->GetCellsVector();

    for (auto &cell : *cells)
    {
        DrawCell(cell, options);
    }
}

void DrawCell(FluidCell* cell, GridDrawOptions* options)
{
    if (options->DrawCellVectors)
        DrawCellVectors(cell, options);

    if (options->DrawCellContents)
        DrawCellContents(cell, options);

    if (options->DrawCellOutline)
        DrawCellOutline(cell, options);
}

void DrawCellContents(FluidCell* cell, GridDrawOptions* options)
{
    auto x = cell->I * options->CellDimensions;
    auto y = cell->J * options->CellDimensions;
    auto z = cell->K * options->CellDimensions;

    if (cell->Type == Empty)
        return;

    if (cell->Type == Solid)
    {
        glColor4f(0.8f, 0.63f, 0.44f, 1.0f);
    }
    else if (cell->Type == Surface)
    {
        glColor4f(0.75f, 0.85f, 0.95f, 1.0f);
    }
    else if (cell->Type == Full)
    {
        glColor4f(0.45f, 0.75f, 0.95f, 1.0f);
    }

    glBegin(GL_POLYGON);

    glVertex3f(x, y, z);

    x += options->CellDimensions;
    glVertex3f(x, y, z);

    y += options->CellDimensions;
    glVertex3f(x, y, z);

    x -= options->CellDimensions;
    glVertex3f(x, y, z);

    y -= options->CellDimensions;
    glVertex3f(x, y, z);

    glEnd();
}

void DrawCellOutline(FluidCell* cell, GridDrawOptions* options)
{
    auto x = cell->I * options->CellDimensions;
    auto y = cell->J * options->CellDimensions;
    auto z = cell->K * options->CellDimensions;

    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glBegin(GL_LINE_LOOP);

    glVertex3f(x, y, z);

    x += options->CellDimensions;
    glVertex3f(x, y, z);

    y += options->CellDimensions;
    glVertex3f(x, y, z);

    x -= options->CellDimensions;
    glVertex3f(x, y, z);

    y -= options->CellDimensions;
    glVertex3f(x, y, z);

    glEnd();
}

void DrawCellVectors(FluidCell* cell, GridDrawOptions* options)
{
    auto x = (cell->I * options->CellDimensions) + (options->CellDimensions / 2);
    auto y = (cell->J * options->CellDimensions) + (options->CellDimensions / 2);
    auto z = 0.0f;

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);

    glVertex3f(x, y, z);

    x += cell->U * options->CellDimensions;
    y += cell->V * options->CellDimensions;
    //z += cell->W * options->CellDimensions;
    glVertex3f(x, y, z);

    glEnd();
}

void DrawParticle(Particle* particle, GridDrawOptions* options)
{
    glPointSize(6.0);
    glColor4f(0.57f, 0.9f, 0.63f, 1.0f);

    glBegin(GL_POINTS);

    glVertex3f(
        particle->X * options->CellDimensions,
        particle->Y * options->CellDimensions,
        particle->Z * options->CellDimensions
    );

    glEnd();
}
