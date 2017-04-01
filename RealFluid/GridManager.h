#pragma once
#include <vector>
#include "src/Core/Fluid/Cell/FluidCell.h"

using namespace std;

class GridManager
{
    public:
    GridManager(int width, int height, int cellDimensions = 20);
    virtual ~GridManager();

    void ConstructGrid();

    private:
    int Width, Height;
    int CellDimensions;

    vector<FluidCell> Grid;
};

