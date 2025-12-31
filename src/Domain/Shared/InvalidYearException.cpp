#include "InvalidYearException.h"

InvalidYearException::InvalidYearException(int year)
    : DomainException("Invalid year: " + std::to_string(year) + ". Must be between 2000 and 2100") {
}
