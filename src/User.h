//
// Created by msullivan on 11/19/24.
//

#pragma once
#include <string>

struct User {
    int userID;
    std::string createdAt;
    std::string name;
    std::string passwordHash;
    std::string email;
    bool isActive;
};

struct Role {
    int roleID;
    std::string name;
    std::string description;
};

struct Team {
    int teamID;
    std::string name;
    std::string description;
};