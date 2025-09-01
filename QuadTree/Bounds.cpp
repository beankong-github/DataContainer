#include "Bounds.h"
#include <math.h>

bool Bounds::Instersect(const Bounds& other) const
{
    // AABB
    if (other.GetX() < MaxX()
        || other.MaxX() < x
        || other.GetY() > MaxY()
        || other.MaxY() < y)
     {
        return false;
     }


    return false;
}
