#include "FluidCell.h"

FluidCell::FluidCell()
{
    I = 0;
    J = 0;
    K = 0;

    Pressure = 0.0;
    U = 0.0;
    V = 0.0;
    W = 0.0;

    Type = Empty;
    Boundary = NotBoundary;
}

FluidCell::~FluidCell()
{
}

Coordinate FluidCell::GetCoordinates() const
{
    return Coordinate(I, J, K);
}

bool FluidCell::IsSolid() const
{
    return Type == Solid;
}

bool FluidCell::IsEmpty() const
{
    return Type == Empty;
}

bool FluidCell::IsFluid() const
{
    return Type == Surface || Type == Full;
}
