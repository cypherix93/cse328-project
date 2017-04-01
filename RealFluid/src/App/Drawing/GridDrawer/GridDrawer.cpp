#include "GridDrawer.h"

void DrawCellGrid(Grid grid)
{
    for each (auto cell in grid.Cells)
    {
        DrawCell(cell);
    }
}

void DrawCell(FluidCell cell)
{
    int x, y;

    x = cell.X;
    y = cell.Y;

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
