#include "Building.h"

Building::Building(int id, string &name, string &address)
{
    buildingId = id;
    buildingName = name;
    buildingAddress = address;
}

int Building::getId() const
{
    return buildingId;
}

string Building::getName() const
{
    return buildingName;
}

string Building::getAddress() const
{
    return buildingAddress;
}