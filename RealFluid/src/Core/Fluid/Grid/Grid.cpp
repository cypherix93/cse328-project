#include "Grid.h"

Grid::Grid(int width, int height, int cellDimensions)
{
    Width = width;
    Height = height;
    CellDimensions = cellDimensions;

    ConstructGrid();
}

Grid::~Grid()
{
    DestructGrid();
}

map<string, FluidCell*>* Grid::GetCellsMap()
{
    return &CellsMap;
}

vector<FluidCell*>* Grid::GetCellsVector()
{
    return &CellsVector;
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
            auto cell = new FluidCell();
            cell->X = CellDimensions * i;
            cell->Y = CellDimensions * j;
            cell->Z = 0;

            cell->Width = cell->Height = cell->Depth = CellDimensions;

            if (j < 2)
                cell->Type = Solid;

            if (cell->Type != Solid)
            {
                cell->U = 40.0;
                cell->V = 10.0;
            }

            CellsVector.push_back(cell);
        }
    }

    for (auto cell : CellsVector)
    {
        CellsMap[GetCellKey(cell->X, cell->Y, cell->Z)] = cell;
    }
}

void Grid::DestructGrid()
{
    for (auto cell : CellsVector)
    {
        free(cell);
    }
}

/* Cell Operations */
FluidCell* Grid::GetCellAtIndex(int i, int j, int k)
{
    auto px = i * CellDimensions;
    auto py = j * CellDimensions;
    auto pz = k * CellDimensions;

    return CellsMap[GetCellKey(px, py, pz)];
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
