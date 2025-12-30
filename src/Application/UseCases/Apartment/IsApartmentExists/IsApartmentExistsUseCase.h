#ifndef ISAPARTMENTEXISTSUSECASE_H
#define ISAPARTMENTEXISTSUSECASE_H
#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Building/Interfaces/IBuildingRepository.h>
using namespace std;

struct IsApartmentExistsParams {
    string apartmentNumber;
    int buildingId;
};

class IsApartmentExistsUseCase : public IUseCase {
private:
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IBuildingRepository> _buildingRepository;
public:
    explicit IsApartmentExistsUseCase(
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IBuildingRepository>& buildingRepository);
    any execute(const any& params = {}) override;
    ~IsApartmentExistsUseCase() override = default;
};
#endif //ISAPARTMENTEXISTSUSECASE_H
