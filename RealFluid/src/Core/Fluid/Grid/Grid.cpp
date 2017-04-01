#include "Grid.h"

Grid::Grid(int width, int height, int cellDimensions)
{
    Width = width;
    Height = height;
    CellDimensions = cellDimensions;
}

Grid::~Grid()
{
}

void Grid::ConstructGrid()
{
    auto xDiv = Width / CellDimensions;
    auto yDiv = Height / CellDimensions;

    for (auto i = 0; i < xDiv; i++)
    {
        for (auto j = 0; j < yDiv; j++)
        {
            FluidCell cell;
            cell.X = CellDimensions * i;
            cell.Y = CellDimensions * j;
            cell.Z = 0;

            cell.Width = cell.Height = CellDimensions;

            if (j < 2)
                cell.Type = Solid;

            Cells.push_back(cell);
        }
    }
}
