#pragma once
#include <map>

#include "../Cell/FluidCell.h"
#include "../../../../GridHelper.h"

using namespace std;

class Grid
{
    public:
    Grid(int width, int height, int cellDimensions);
    virtual ~Grid();

    // Grid Operations
    map<string, FluidCell>* GetCells();

    void ConstructGrid();

    // Cell Operations
    FluidCell* GetCellAtIndex(int x, int y, int z);
    FluidCell* GetCellAtPixel(int x, int y, int z);

    private:
    map<string, FluidCell> Cells;

    int Width, Height;
    int CellDimensions;
};

