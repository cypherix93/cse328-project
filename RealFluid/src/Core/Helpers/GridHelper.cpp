#include "GridHelper.h"

string GetCellKey(int i, int j, int k)
{
    stringstream stream;
    stream << i << "," << j << "," << k;

    return stream.str();
}
