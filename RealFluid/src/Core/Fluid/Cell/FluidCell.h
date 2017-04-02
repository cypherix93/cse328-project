#pragma once

#include <GL/glew.h>
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
    ~FluidCell();

    FluidCellType Type;

    int X, Y, Z;
    int Width, Height, Depth;

    int U, V, W;
    float Pressure;

    // Getters
    vector<int> GetPosition() const;

    // Drawers
    void DrawContents() const;
    void DrawOutline() const;
    void DrawVectors() const;
};

