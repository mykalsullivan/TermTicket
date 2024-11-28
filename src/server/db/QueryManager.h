//
// Created by msullivan on 11/27/24.
//

#pragma once
#include "DatabaseConnection.h"
#include <pqxx/pqxx>

class QueryManager {
public:
    explicit QueryManager(DatabaseConnection &connection);
    ~QueryManager();

private:
    DatabaseConnection &m_Connection;
    pqxx::connection *m_DatabaseConnection;

public:
    bool connect(const std::string &connectionString);
    void disconnect() const;
    pqxx::result executeQuery(const std::string &query);
    [[nodiscard]] static std::string getQueryFromFile(const std::string &filename);
};