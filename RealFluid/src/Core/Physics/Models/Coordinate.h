#pragma once

class Coordinate
{
    public:
    float X, Y, Z;

    explicit Coordinate(float x = 0.0, float y = 0.0, float z = 0.0)
    {
        X = x;
        Y = y;
        Z = z;
    }

    virtual ~Coordinate()
    {
    }
};