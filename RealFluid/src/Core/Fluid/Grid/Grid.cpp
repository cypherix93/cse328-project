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

vector<Particle*>* Grid::GetParticlesVector()
{
    return &ParticlesVector;
}

void Grid::ConstructGrid()
{
    CellsX = Width / CellDimensions;
    CellsY = Height / CellDimensions;
    CellsZ = 1;

    for (auto i = 0; i < CellsX; i++)
    {
        for (auto j = 0; j < CellsY; j++)
        {
            auto cell = new FluidCell();
            cell->X = CellDimensions * i;
            cell->Y = CellDimensions * j;
            cell->Z = 0;

            cell->Width = cell->Height = cell->Depth = CellDimensions;

            if (j < 2 || (i < 1 && j < CellsY - 3) || (i > CellsX - 2 && j < CellsY - 3))
            {
                cell->Type = Solid;
            }

            if (cell->Type != Solid && i < 1)
            {
                cell->Boundary = Inflow;
                cell->U = 20.0;
            }

            CellsVector.push_back(cell);
        }
    }

    for (auto cell : CellsVector)
    {
        auto index = GetCellIndex(cell->X, cell->Y, cell->Z);
        CellsMap[Helpers::GetCellKey(index[0], index[1], index[2])] = cell;
    }
}

void Grid::DestructGrid()
{
    for (auto cell : CellsVector)
    {
        free(cell);
    }
    for (auto particle : ParticlesVector)
    {
        free(particle);
    }
    CellsVector.clear();
    CellsMap.clear();
    ParticlesVector.clear();
}

/* Cell Operations */
FluidCell* Grid::GetCellAtIndex(int i, int j, int k)
{
    return CellsMap[Helpers::GetCellKey(i, j, k)];
}

FluidCell* Grid::GetCellAtPixel(int x, int y, int z)
{
    auto index = GetCellIndex(x, y, z);

    return GetCellAtIndex(index[0], index[1], index[2]);
}

vector<int> Grid::GetCellIndex(int x, int y, int z)
{
    auto i = x / CellDimensions;
    auto j = y / CellDimensions;
    auto k = z / CellDimensions;

    return{ i, j, k };
}

void Grid::AddParticle(FluidCell* cell)
{
    int x, y, z;
    x = cell->X;
    y = cell->Y;
    z = cell->Z;

    ParticlesVector.push_back(new Particle(x, y, z));
}
