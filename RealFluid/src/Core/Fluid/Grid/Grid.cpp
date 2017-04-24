#include "Grid.h"

#include <Core/Helpers/GridHelper/GridHelper.h>

Grid::Grid(int xCells, int yCells, int zCells)
{
    CellsX = xCells;
    CellsY = yCells;
    CellsZ = zCells;

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
    for (auto i = 0; i < CellsX; i++)
    {
        for (auto j = 0; j < CellsY; j++)
        {
            auto cell = new FluidCell();
            cell->X = i;
            cell->Y = j;
            cell->Z = 0;

            if (j < 2 || (i < 1 && j < CellsY - 3) || (i > CellsX - 2 && j < CellsY - 3))
            {
                cell->Type = Solid;
            }

            if (cell->Type != Solid && i < 1)
            {
                cell->Boundary = Inflow;
                cell->U = 1.2f;
            }

            CellsVector.push_back(cell);
        }
    }

    for (auto cell : CellsVector)
    {
        CellsMap[Helpers::GetCellKey(cell->X, cell->Y, cell->Z)] = cell;
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

void Grid::AddParticle(FluidCell* cell)
{
    int x, y, z;
    x = cell->X + 0.5f;
    y = cell->Y + 0.5f;
    z = cell->Z;

    ParticlesVector.push_back(new Particle(x, y, z));
}
