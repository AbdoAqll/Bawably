#include <string>

using namespace std;

class Tenant
{
private:
    int tenantId;
    int apartmentId;
    string fullName;
    string nationalId;
    string phoneNumber;
    string moveInDate;
    string moveOutDate;

public:
    Tenant(int id, int apartmentId, string &name, string &nationalId, string &phone, string &moveInDate);
    int getTenantId() const;
    int getApartmentId() const;
    string getFullName() const;
    string getNationalId() const;
    string getPhoneNumber() const;
    string getMoveInDate() const;
    string getMoveOutDate() const;

    void setPhoneNumber(string &phone);
    void setMoveOutDate(string &date);
    void moveToApartment(int newApartmentId);
};