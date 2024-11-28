//
// Created by msullivan on 11/27/24.
//

#pragma once
#include "DatabaseConnection.h"

class AuthenticationManager {
public:
    explicit AuthenticationManager(DatabaseConnection &connection);
    ~AuthenticationManager();

private:
    DatabaseConnection &m_Connection;
    bool m_Authenticated;

public:
    bool authenticate(const std::string &username, const std::string &password);
    void unauthenticate();
    [[nodiscard]] bool isAuthenticated() const { return m_Authenticated; }
};
