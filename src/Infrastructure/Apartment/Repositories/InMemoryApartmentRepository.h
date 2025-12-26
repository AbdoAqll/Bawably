#ifndef INMEMORYAPARTMENTREPOSITORY_H
#define INMEMORYAPARTMENTREPOSITORY_H
#include <unordered_map>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>

class InMemoryApartmentRepository : public IApartmentRepository {
private:
    unordered_map<int, Apartment> apartments;
public:
    InMemoryApartmentRepository() = default;

    ~InMemoryApartmentRepository() override = default;

    bool save(const Apartment &apartment) override;

    Apartment findById(int id, int buildingId) override;

    bool exists(int id, int buildingId) override;

    vector<Apartment> getAll(int buildingId) override;

    int getApartmentIdFromApartmentNumber(string apartmentNumber) override;
};
#endif //INMEMORYAPARTMENTREPOSITORY_H
