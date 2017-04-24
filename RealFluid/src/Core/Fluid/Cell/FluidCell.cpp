#include "FluidCell.h"

FluidCell::FluidCell()
{
    X = 0;
    Y = 0;
    Z = 0;
    
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
    return Coordinate(X, Y, Z);
}