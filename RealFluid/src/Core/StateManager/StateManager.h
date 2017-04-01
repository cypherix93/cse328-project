#pragma once

enum ApplicationState
{
    Cube,
    Tetrahedron,
    Sphere,
    Quadrics,
    Ellipsoid
};

class StateManager
{
    public:
    StateManager();
    ~StateManager();

    ApplicationState State;
};

