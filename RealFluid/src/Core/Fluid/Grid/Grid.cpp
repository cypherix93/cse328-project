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

map<string, FluidCell>* Grid::GetCells()
{
    return &Cells;
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

            cell.Width = cell.Height = cell.Depth = CellDimensions;

            if (j < 2)
                cell.Type = Solid;

            Cells[GetCellKey(cell.X, cell.Y, cell.Z)] = cell;
        }
    }
}

FluidCell* Grid::GetCellAtIndex(int x, int y, int z)
{
    auto px = x * CellDimensions;
    auto py = y * CellDimensions;
    auto pz = z * CellDimensions;

    return &Cells[GetCellKey(px, py, pz)];
}

FluidCell* Grid::GetCellAtPixel(int x, int y, int z)
{
    auto cx = x / CellDimensions;
    auto cy = y / CellDimensions;
    auto cz = z / CellDimensions;

    return GetCellAtIndex(cx, cy, cz);
}
