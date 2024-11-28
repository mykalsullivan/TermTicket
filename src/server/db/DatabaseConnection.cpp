//
// Created by msullivan on 11/18/24.
//

#include "DatabaseConnection.h"
#include "QueryManager.h"
#include "TicketManager.h"
#include "AuthenticationManager.h"
#include "UserManager.h"
#include <iostream>

DatabaseConnection::DatabaseConnection(
    const std::string &username, const std::string &password,
    const std::string &host, int port)
{
    std::string connectionString = "dbname=term_ticket"
                                   " user=" + username +
                                   " password=" + password +
                                   " host=" + host +
                                   " port=" + std::to_string(port);
    m_Connection = new pqxx::connection(connectionString);

    // Connect to database
    if (!m_Connection->is_open())
    {
        std::cerr << "Failed to connect to database\n";
        exit(EXIT_FAILURE);
    }

    // Set up managers
    m_QueryManager = new QueryManager(*this);
    m_TicketManager = new TicketManager(*this);
    m_AuthenticationManager = new AuthenticationManager(*this);
    m_UserManager = new UserManager(*this);
}

DatabaseConnection::~DatabaseConnection()
{
    if (m_Connection->is_open())
        disconnect();
}

void DatabaseConnection::disconnect()
{
    m_Connection->disconnect();
}