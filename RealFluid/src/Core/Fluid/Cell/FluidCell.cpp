#include "FluidCell.h"

FluidCell::FluidCell()
{
    X = 0;
    Y = 0;
    Z = 0;

    U = 0;
    V = 0;
    W = 0;

    Width = 0;
    Height = 0;
    Depth = 0;

    Type = Empty;
}

FluidCell::~FluidCell()
{
}

vector<int> FluidCell::GetPosition()
{
    return{ X, Y, Z };
}
