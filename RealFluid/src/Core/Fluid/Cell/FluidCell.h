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

    vector<float> GetPosition();
    vector<float> GetDimensions();

    protected:
    FluidCellType Type;

    float X, Y, Z;
    float Width, Height;

    float U, V, W;
};

