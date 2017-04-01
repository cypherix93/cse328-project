#pragma once

#include <vector>

using namespace std;

enum FluidCellType
{
    Empty,
    Full,
    Surface,
    Solid
};

class FluidCell
{
    public:
    FluidCell();
    virtual ~FluidCell();

    FluidCellType Type;

    int X, Y, Z;
    int Width, Height, Depth;

    float U, V, W;

    vector<int> GetPosition();
};

