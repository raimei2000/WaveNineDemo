#include "FloatArrayRow.h"

float& FFloatArrayRow::operator[](int32 Index)
{
    return RowValues[Index];
}

const float& FFloatArrayRow::operator[](int32 Index) const
{
    return RowValues[Index];
}
