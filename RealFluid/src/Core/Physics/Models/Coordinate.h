#pragma once

class Coordinate
{
    public:
    int X, Y, Z;

    explicit Coordinate(int x = 0, int y = 0, int z = 0)
    {
        X = x;
        Y = y;
        Z = z;
    }

    virtual ~Coordinate()
    {
    }
};