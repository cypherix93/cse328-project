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

void DrawCellGrid(Grid grid, GridDrawOptions* options)
{
    if (options == nullptr)
        options = new GridDrawOptions();

    for each (auto cell in grid.Cells)
    {
        DrawCell(cell, options->DrawCellContents, options->DrawCellOutline, options->DrawCellVectors);
    }
}

void DrawCell(FluidCell cell, bool drawContents, bool drawOutline, bool drawVectors)
{
    if (drawContents)
        cell.DrawContents();

    if (drawOutline)
        cell.DrawOutline();

    if (drawVectors)
        cell.DrawVectors();
}