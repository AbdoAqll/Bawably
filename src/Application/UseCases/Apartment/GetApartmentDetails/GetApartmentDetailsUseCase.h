#ifndef GETAPARTMENTSTATUSUSECASE_H
#define GETAPARTMENTSTATUSUSECASE_H
#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Building/Interfaces/IBuildingRepository.h>

struct GetApartmentDetailsParams {
    string aprtmentNumber;
    int buildingId;
};

class GetApartmentDetailsUseCase : public IUseCase {
private:
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IBuildingRepository> _buildingRepository;
public:
    explicit GetApartmentDetailsUseCase(
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IBuildingRepository>& buildingRepository);
    any execute(const any& params = {}) override;
    ~GetApartmentDetailsUseCase() override = default;
};
#endif //GETAPARTMENTSTATUSUSECASE_H
