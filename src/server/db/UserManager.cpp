//
// Created by msullivan on 11/27/24.
//

#include "UserManager.h"
#include <iostream>

UserManager::UserManager(DatabaseConnection &connection) : m_Connection(connection)
{}

UserManager::~UserManager()
{}

/* Users */
bool UserManager::addUser(const User &user)
{

    return false;
}

bool UserManager::deleteUser(int userID)
{

    return false;
}

bool UserManager::editUser(int userID, const User &user)
{

    return false;
}

User UserManager::getUser(int userID)
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "SELECT * FROM users "
                        "WHERE user_id = $1;";
    pqxx::result result;

    // Execute query
    try
    {
        result = work.exec_params(query, userID);
        work.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return {};
    }

    // Retrieve user if there is a result
    User user {};
    if (!result.empty())
    {
        user.userID = result[0]["user_id"].as<int>();
        user.createdAt = result[0]["created_at"].as<std::string>();
        user.username = result[0]["username"].as<std::string>();
        user.passwordHash = result[0]["password_hash"].as<std::string>();
        user.email = result[0]["email"].as<std::string>();
        user.isActive = result[0]["is_active"].as<bool>();
    }
    return user;
}

std::vector<User> UserManager::getUsers()
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "SELECT * FROM users;";
    pqxx::result result;

    // Execute query
    try
    {
        result = work.exec(query);
        work.commit();

        // Retrieve users
        std::vector<User> users;
        for (const auto &row : result)
        {
            User user {};
            user.userID = row["user_id"].as<int>();
            user.createdAt = row["created_at"].as<std::string>();
            user.username = row["username"].as<std::string>();
            user.passwordHash = row["password_hash"].as<std::string>();

            if (row["email"].is_null())
                user.email = "(not set)";
            else
                user.email = row["email"].as<std::string>();

            user.isActive = row["is_active"].as<bool>();
            users.emplace_back(user);
        }
        return users;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return {};
    }
}