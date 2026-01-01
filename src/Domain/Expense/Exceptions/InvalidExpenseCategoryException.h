#ifndef INVALIDEXPENSECATEGORYEXCEPTION_H
#define INVALIDEXPENSECATEGORYEXCEPTION_H

#include <Shared/DomainException.h>

class InvalidExpenseCategoryException : public DomainException {
public:
    explicit InvalidExpenseCategoryException(int categoryValue);
};

#endif //INVALIDEXPENSECATEGORYEXCEPTION_H