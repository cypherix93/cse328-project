#pragma once

class Coordinate
{
    public:
    int X, Y, Z;

    explicit Coordinate(int x = 1, int y = 1, int z = 1)
    {
        X = x;
        Y = y;
        Z = z;
    }

    virtual ~Coordinate()
    {
    }
};