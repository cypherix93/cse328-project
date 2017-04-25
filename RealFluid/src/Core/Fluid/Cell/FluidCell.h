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

    float I, J, K;

    float Width = 1.0f, Height = 1.0f, Depth = 1.0f;

    float U, V, W;
    float Pressure;

    // Getters
    Coordinate GetCoordinates() const;
};

