//
// Created by msullivan on 11/27/24.
//

#pragma once
#include "DatabaseConnection.h"
#include "User.h"

class UserManager {
public:
    explicit UserManager(DatabaseConnection &connection);
    ~UserManager();

private:
    DatabaseConnection &m_Connection;

public:
    /* Users */
    bool addUser(const User &user);
    bool deleteUser(int userID);
    bool editUser(int userID, const User &user);
    User getUser(int userID);
    std::vector<User> getUsers();

    /* Teams */
    bool addUserToTeam(int userID, int teamID);
    bool removeUserFromTeam(int userID, int teamID);
    std::vector<User> getUsersFromTeam(int teamID);
    std::vector<Team> getTeams();
};