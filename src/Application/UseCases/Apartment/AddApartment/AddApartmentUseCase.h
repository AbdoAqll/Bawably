#ifndef ADDAPARTMENTUSECASE_H
#define ADDAPARTMENTUSECASE_H
#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Building/Interfaces/IBuildingRepository.h>
using namespace std;

struct AddApartmentParams {
    int buildingId;
    string apartmentNumber;
};

class AddApartmentUseCase : public IUseCase {
private:
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IBuildingRepository> _buildingRepository;
public:
    explicit AddApartmentUseCase(
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IBuildingRepository>& buildingRepository);
    any execute(const any& params = {}) override;
    ~AddApartmentUseCase() override = default;
};
#endif //ADDAPARTMENTUSECASE_H
