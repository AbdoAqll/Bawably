#ifndef APARTMENTCONTROLLER_H
#define APARTMENTCONTROLLER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <UseCases/IUseCase.h>
using namespace std;

class ApartmentController {
private:
    std::unordered_map<string, shared_ptr<IUseCase>> useCases;

public:
    explicit ApartmentController(vector<shared_ptr<IUseCase>>& useCases);
    void displayMenu();
    void createApartment(int buildingId);
    void getAllApartments(int buildingId);
    void getApartmentDetails(int buildingId);
    void checkApartmentStatus(int buildingId);
    void isApartmentExists(int buildingId);
    void execute(int buildingId);
    ~ApartmentController() = default;
};
#endif //APARTMENTCONTROLLER_H
