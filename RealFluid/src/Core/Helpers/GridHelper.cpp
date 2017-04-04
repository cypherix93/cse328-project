#include "GridHelper.h"

string GetCellKey(int x, int y, int z)
{
    stringstream stream;
    stream << x << "," << y << "," << z;

    return stream.str();
}
