#ifndef I_USE_CASE_H
#define I_USE_CASE_H

#include <string>
#include <any>
using namespace std;
class IUseCase {
public:
    string UseCaseName;
    virtual ~IUseCase() = default;
    virtual any execute(const any& params = {}) = 0;
};

#endif