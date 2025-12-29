#ifndef CHECKAPARTMENTEXISTSANDGETIDUSECASE_H
#define CHECKAPARTMENTEXISTSANDGETIDUSECASE_H
#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Building/Interfaces/IBuildingRepository.h>
using namespace std;

struct CheckApartmentExistsAndGetIdParams {
    string apartmentNumber;
    int buildingId;
};

class CheckApartmentExistsAndGetIdUseCase : public IUseCase {
private:
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IBuildingRepository> _buildingRepository;
public:
    explicit CheckApartmentExistsAndGetIdUseCase(
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IBuildingRepository>& buildingRepository);
    any execute(const any& params = {}) override;
    ~CheckApartmentExistsAndGetIdUseCase() override = default;
};
#endif //CHECKAPARTMENTEXISTSANDGETIDUSECASE_H