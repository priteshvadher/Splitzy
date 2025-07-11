#pragma once
#include <string>

class User {
    std::string userId;
    std::string name;
public:
    User(const std::string& userId, const std::string& name) : userId(userId), name(name) {}
    const std::string& getUserId() const { return userId; }
    const std::string& getName() const { return name; }
}; 