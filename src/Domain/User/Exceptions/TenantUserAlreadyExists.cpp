#include "TenantUserAlreadyExists.h"
using namespace std;

TenantUserAlreadyExists::TenantUserAlreadyExists(string tenantUserName)
    : DomainException("Username: " + tenantUserName + " is already taken.")

{

}

TenantUserAlreadyExists::TenantUserAlreadyExists(int tenantId)
    : DomainException("Tenant with Id: " + to_string(tenantId) + " already exists.")
{

}
