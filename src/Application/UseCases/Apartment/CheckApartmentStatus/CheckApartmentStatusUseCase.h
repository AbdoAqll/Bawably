#ifndef CHECKAPARTMENTSTATUS_H
#define CHECKAPARTMENTSTATUS_H
#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Building/Interfaces/IBuildingRepository.h>
using namespace std;

struct CheckApartmentStatusParams {
    string apartmentNumber;
    int buildingId;
};

class CheckApartmentStatusUseCase : public IUseCase {
private:
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IBuildingRepository> _buildingRepository;
public:
    explicit CheckApartmentStatusUseCase(
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IBuildingRepository>& buildingRepository);
    any execute(const any& params = {}) override;
    ~CheckApartmentStatusUseCase() override = default;
};
#endif //CHECKAPARTMENTSTATUS_H
