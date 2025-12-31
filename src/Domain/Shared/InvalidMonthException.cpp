#include "InvalidMonthException.h"

InvalidMonthException::InvalidMonthException(int month)
    : DomainException("Invalid month: " + std::to_string(month) + ". Must be between 1 and 12") {
}
