#pragma once
#include <string>

using namespace std;

class RentalContract {
private:
    int contractId;
    int apartmentId;
    int tenantId;
    double monthlyRent;
    string startDate;
    string endDate;
    bool isActive;

public:
    RentalContract(int id, int apartmentId, int tenantId, double monthlyRent, string& startDate);

    int getContractId() const;
    int getApartmentId() const;
    int getTenantId() const;
    double getMonthlyRent() const;
    string getStartDate() const;
    string getEndDate() const;
    bool getIsActive() const;

    void setEndDate(string& newEndDate);

    void terminateContract(string& terminationDate);
};