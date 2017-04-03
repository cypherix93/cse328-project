#include "GridDrawer.h"

GridDrawOptions::GridDrawOptions()
{
    DrawCellContents = true;
    DrawCellOutline = true;
    DrawCellVectors = true;
}

GridDrawOptions::~GridDrawOptions()
{
}

void DrawCellGrid(Grid* grid, GridDrawOptions* options)
{
    if (options == nullptr)
        options = new GridDrawOptions();

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