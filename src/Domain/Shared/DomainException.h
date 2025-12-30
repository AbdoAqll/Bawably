#ifndef DOMAINEXCEPTION_H
#define DOMAINEXCEPTION_H
#include <stdexcept>
#include <string>
using namespace std;
class DomainException : public exception {
private:
    string _message;

public:
    explicit DomainException (const string& message);

    const char* what() const noexcept override;
};
#endif //DOMAINEXCEPTION_H
