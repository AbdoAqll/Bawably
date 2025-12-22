#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int id;
    std::string name;
    std::string email;

public:
    User() : id(0), name(""), email("") {}

    User(int userId, const std::string &userName, const std::string &userEmail)
        : id(userId), name(userName), email(userEmail) {}

    // Getters
    int getId() const { return id; }
    const std::string &getName() const { return name; }
    const std::string &getEmail() const { return email; }

    // Setters
    void setId(int userId) { id = userId; }
    void setName(const std::string &userName) { name = userName; }
    void setEmail(const std::string &userEmail) { email = userEmail; }
};

#endif // USER_H
