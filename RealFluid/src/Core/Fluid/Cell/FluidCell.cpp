#include "FluidCell.h"

FluidCell::FluidCell()
{
    X = 0;
    Y = 0;
    Z = 0;

    Width = 0;
    Height = 0;
    Depth = 0;

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

void FluidCell::DrawContents() const
{
    auto x = X;
    auto y = Y;
    auto z = Z;

    if (Type == Empty)
        return;

    if (Type == Solid)
    {
        glColor4f(0.8f, 0.63f, 0.44f, 1.0f);
    }
    else if (Type == Surface)
    {
        glColor4f(0.75f, 0.85f, 0.95f, 1.0f);
    }
    else if (Type == Full)
    {
        glColor4f(0.45f, 0.75f, 0.95f, 1.0f);
    }

    glBegin(GL_POLYGON);

    glVertex3i(x, y, z);

    x += Width;
    glVertex3i(x, y, z);

    y += Height;
    glVertex3i(x, y, z);

    x -= Width;
    glVertex3i(x, y, z);

    y -= Height;
    glVertex3i(x, y, z);

    glEnd();
}

void FluidCell::DrawOutline() const
{
    auto x = X;
    auto y = Y;
    auto z = Z;

    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    glBegin(GL_LINE_LOOP);

    glVertex3i(x, y, z);

    x += Width;
    glVertex3i(x, y, z);

    y += Height;
    glVertex3i(x, y, z);

    x -= Width;
    glVertex3i(x, y, z);

    y -= Height;
    glVertex3i(x, y, z);

    glEnd();
}

void FluidCell::DrawVectors() const
{
    auto x = X + (Width / 2);
    auto y = Y + (Height / 2);
    auto z = 0;

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);

    glVertex3i(x, y, z);

    x += U;
    y += V;
    z += W;
    glVertex3i(x, y, z);

    glEnd();
}

