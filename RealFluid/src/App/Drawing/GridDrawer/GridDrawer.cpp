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

    for (auto cell : grid->Cells)
    {
        DrawCell(cell, *options);
    }
}

void DrawCell(FluidCell cell, GridDrawOptions options)
{
    if (options.DrawCellContents)
        cell.DrawContents();

    if (options.DrawCellOutline)
        cell.DrawOutline();

    if (options.DrawCellVectors)
        cell.DrawVectors();
}