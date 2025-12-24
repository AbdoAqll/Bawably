#include <string>
using namespace std;

class Building
{
private:
    int buildingId;
    string buildingName;
    string buildingAddress;

public:
    Building(int id, string &name, string &address);
    int getId() const;
    string getName() const;
    string getAddress() const;
};