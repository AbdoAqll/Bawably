#include "InvalidExpenseDateException.h"

InvalidExpenseDateException::InvalidExpenseDateException(const std::string message)
    : DomainException(message) {
}