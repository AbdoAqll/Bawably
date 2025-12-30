#ifndef BUILDING_H
#define BUILDING_H

#include <string>
using namespace std;

class Building
{
private:
    int buildingId;
    string buildingName;
    string buildingAddress;
    static int nextId;

public:
    Building(string &name, string &address);
    int getId() const;
    string getName() const;
    string getAddress() const;
};

#endif