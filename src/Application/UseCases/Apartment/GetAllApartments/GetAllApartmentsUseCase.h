#ifndef GETALLAPARTMENTSUSECASE_H
#define GETALLAPARTMENTSUSECASE_H
#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Building/Interfaces/IBuildingRepository.h>
using namespace std;

struct GetAllApartmentArgs {
    int buildingId;
};

class GetAllApartmentsUseCase : public IUseCase {
private:
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IBuildingRepository> _buildingRepository;
public:
    explicit GetAllApartmentsUseCase(
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IBuildingRepository>& buildingRepository);
    any execute(const any& params = {}) override;
    ~GetAllApartmentsUseCase() override = default;
};
#endif //GETALLAPARTMENTSUSECASE_H
