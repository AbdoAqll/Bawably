#include "TenantUserNotFound.h"
using namespace std;

TenantUserNotFound::TenantUserNotFound(int tenantId)
    : DomainException("Tenant with Id: " + to_string(tenantId) + " not Found.")
{

}
