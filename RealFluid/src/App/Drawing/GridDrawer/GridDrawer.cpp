#include "GridDrawer.h"

GridDrawOptions::GridDrawOptions()
{
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
            DrawParticle(particle);
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
        cell->DrawVectors();

    if (options->DrawCellOutline)
        cell->DrawOutline();

    if (options->DrawCellContents)
        cell->DrawContents();
}

void DrawParticle(Particle* particle)
{
    glPointSize(6.0);
    glColor4f(0.57f, 0.9f, 0.63f, 1.0f);

    glBegin(GL_POINTS);

    glVertex3i(particle->X, particle->Y, particle->Z);

    glEnd();
}
