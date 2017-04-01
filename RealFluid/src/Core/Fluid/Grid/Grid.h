#pragma once
#include <vector>
#include "../Cell/FluidCell.h"

using namespace std;

class Grid
{
    public:
    Grid(int width, int height, int cellDimensions);
    virtual ~Grid();

    vector<FluidCell> Cells;

    void ConstructGrid();

    private:
    int Width, Height;
    int CellDimensions;
};

