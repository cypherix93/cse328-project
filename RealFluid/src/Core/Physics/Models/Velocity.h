#pragma once

class Velocity
{
    public:
    float U, V, W;

    explicit Velocity(float u = 0.0, float v = 0.0, float w = 0.0)
    {
        U = u;
        V = v;
        W = w;
    }

    virtual ~Velocity()
    {
    }
};