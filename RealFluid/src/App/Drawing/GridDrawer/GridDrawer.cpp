#include "GridDrawer.h"

GridDrawOptions::GridDrawOptions()
{
    DrawCellContents = true;
    DrawCellOutline = true;
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
        DrawCell(cell, options->DrawCellOutline, options->DrawCellContents);
    }
}

void DrawCell(FluidCell cell, bool drawOutline, bool drawContents)
{
    if (drawOutline)
        DrawCellOutline(cell);

    if (drawContents)
        DrawCellContents(cell);
}

void DrawCellOutline(FluidCell cell)
{
    auto x = cell.X;
    auto y = cell.Y;

    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glBegin(GL_LINE_LOOP);

    glVertex2i(x, y);

    x += cell.Width;
    glVertex2i(x, y);

    y += cell.Height;
    glVertex2i(x, y);

    x -= cell.Width;
    glVertex2i(x, y);

    y -= cell.Height;
    glVertex2i(x, y);

    glEnd();
}

void DrawCellContents(FluidCell cell)
{
    auto x = cell.X;
    auto y = cell.Y;

    if (cell.Type == Empty)
        return;

    if (cell.Type == Solid)
    {
        glColor4f(0.48f, 0.28f, 0.0f, 1.0f);

        glBegin(GL_POLYGON);

        glVertex2i(x, y);

        x += cell.Width;
        glVertex2i(x, y);

        y += cell.Height;
        glVertex2i(x, y);

        x -= cell.Width;
        glVertex2i(x, y);

        y -= cell.Height;
        glVertex2i(x, y);

        glEnd();
    }
}
