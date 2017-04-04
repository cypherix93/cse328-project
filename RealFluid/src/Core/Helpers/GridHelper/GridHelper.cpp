#include "GridHelper.h"

string Helpers::GetCellKey(int i, int j, int k)
{
    stringstream stream;
    stream << i << "," << j << "," << k;

    return stream.str();
}
