#ifndef BUILDINGNOTEXISTEXCEPTION_H
#define BUILDINGNOTEXISTEXCEPTION_H
#include <Shared/DomainException.h>
#include <string>
using namespace std;

class BuildingNotExistException : public DomainException {
public:
    explicit BuildingNotExistException(int buildingId);
};
#endif //BUILDINGNOTEXISTEXCEPTION_H
