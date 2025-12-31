#ifndef IAPARTMENTREPOSITORY_H
#define IAPARTMENTREPOSITORY_H
#include "Domain/Apartment/Apartment.h"
#include <vector>
using namespace std;

class IApartmentRepository {
public:
    virtual ~IApartmentRepository() = default;

    virtual bool save(const Apartment& apartment) = 0;
    virtual Apartment findById(int id, int buildingId) = 0;
    virtual Apartment findById(int id) = 0;
    virtual bool exists(int id, int buildingId) = 0;
    virtual vector<Apartment> getAll(int buildingId) = 0;
    virtual int getApartmentIdFromApartmentNumber(string apartmentNumber, int buildingId) = 0;
};
#endif //IAPARTMENTREPOSITORY_H
