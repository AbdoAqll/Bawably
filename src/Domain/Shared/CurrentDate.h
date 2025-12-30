#ifndef CURRENTDATE_H
#define CURRENTDATE_H

#include <iomanip> // For std::put_time
#include <sstream> // For std::ostringstream
#include <ctime>   // For std::time and std::localtime

class CurrentDate {
public:
    static std::string getCurrentDateString();

};

#endif