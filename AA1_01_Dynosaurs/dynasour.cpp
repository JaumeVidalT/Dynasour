#include "dynasour.h"

DynosaurType Dynosaur::GetType() const
{
    return type;
}

std::string Dynosaur::GetName() const
{
    return name;
}

int Dynosaur::GetStrength() const
{
    return health + attackPower;
}
