#ifndef EXPENSENOTFOUNDEXCEPTION_H
#define EXPENSENOTFOUNDEXCEPTION_H

#include <Shared/DomainException.h>

class ExpenseNotFoundException : public DomainException {
public:
    explicit ExpenseNotFoundException(int expenseId);
};

#endif //EXPENSENOTFOUNDEXCEPTION_H