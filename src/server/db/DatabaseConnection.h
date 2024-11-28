//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <pqxx/pqxx>

// Forward declaration(s)
class QueryManager;
class TicketManager;
class AuthenticationManager;
class UserManager;

class DatabaseConnection {
public:
    DatabaseConnection(const std::string& username, const std::string& password, const std::string& host, int port);
    ~DatabaseConnection();

private:
    pqxx::connection *m_Connection;

    QueryManager *m_QueryManager;
    TicketManager *m_TicketManager;
    AuthenticationManager *m_AuthenticationManager;
    UserManager *m_UserManager;

public:
    void disconnect();
    auto &queryManager() { return m_QueryManager; }
    auto &ticketManager() { return m_TicketManager; }
    auto &authenticationManager() { return m_AuthenticationManager; }
    auto &userManager() { return m_UserManager; }

    bool resetDatabase() const;
};