#include "Obj.h"

float Obj::Pitagoras(float x, float y)
{
    return sqrt(pow(Move.x, 2) + pow(Move.y, 2));
}

float Obj::deg_to_rad(float deg)
{
    return (deg-90)*(M_PI/180.f);
}

bool Obj::Chcek_lives()
{
    if(live>0)
        return false;
    return true;
}
