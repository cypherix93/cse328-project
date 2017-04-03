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
    CellsX = Width / CellDimensions;
    CellsY = Height / CellDimensions;
    CellsZ = 0;

    for (auto i = 0; i < CellsX; i++)
    {
        for (auto j = 0; j < CellsY; j++)
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

FluidCell* Grid::GetCellAtIndex(int i, int j, int k)
{
    auto px = i * CellDimensions;
    auto py = j * CellDimensions;
    auto pz = k * CellDimensions;

    return &Cells[GetCellKey(px, py, pz)];
}

FluidCell* Grid::GetCellAtPixel(int x, int y, int z)
{
    auto cx = x / CellDimensions;
    auto cy = y / CellDimensions;
    auto cz = z / CellDimensions;

    return GetCellAtIndex(cx, cy, cz);
}

vector<int> Grid::GetCellIndex(FluidCell* cell)
{
    auto cx = cell->X / CellDimensions;
    auto cy = cell->Y / CellDimensions;
    auto cz = cell->Z / CellDimensions;

    return{ cx, cy, cz };
}
