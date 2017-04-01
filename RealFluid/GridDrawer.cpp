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
    auto position = cell.GetPosition();
    auto pos_p = &position[0];

    glBegin(GL_LINES);

    glVertex3iv(pos_p);
    
    position[0] += cell.Width;
    glVertex3iv(pos_p);

    position[1] += cell.Height;
    glVertex3iv(pos_p);

    position[0] -= cell.Width;
    glVertex3iv(pos_p);

    position[1] -= cell.Height;
    glVertex3iv(pos_p);

    glEnd();
}
