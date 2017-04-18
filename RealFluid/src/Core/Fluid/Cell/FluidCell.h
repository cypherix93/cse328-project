#pragma once

#include <GL/glew.h>
#include <vector>
#include <Core/Physics/Models/Coordinate.h>

using namespace std;

enum FluidCellType
{
    Empty,
    Full,
    Surface,
    Solid
};

enum BoundaryType
{
    Inflow,
    Outflow,
    NotBoundary
};

class FluidCell
{
    public:
    FluidCell();
    ~FluidCell();

    FluidCellType Type;
    BoundaryType Boundary;

    int X, Y, Z;
    int Width, Height, Depth;

    float U, V, W;
    float Pressure;

    // Getters
    Coordinate GetCoordinates() const;

    // Drawers
    void DrawContents() const;
    void DrawOutline() const;
    void DrawVectors() const;
};

