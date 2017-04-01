#pragma once
#include <vector>
#include "src/Core/Fluid/Cell/FluidCell.h"

using namespace std;

class GridManager
{
    public:
    GridManager();
    virtual ~GridManager();

    vector<FluidCell> ConstructGrid(int width, int height);
};

