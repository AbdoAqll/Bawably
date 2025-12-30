#include "CurrentDate.h"

std::string CurrentDate::getCurrentDateString() {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);

    std::ostringstream oss;
    // %Y = Year (2025), %m = Month (12), %d = Day (26)
    oss << std::put_time(ltm, "%d/%m/%Y::%H:%M:%S");
    return oss.str();
}