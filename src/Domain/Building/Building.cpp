#include "Building.h"

int Building::nextId=0;

Building::Building(string &name, string &address)
{
    buildingId = ++nextId;
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
