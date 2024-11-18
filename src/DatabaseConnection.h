//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <pqxx/pqxx>

class DatabaseConnection {
public:
    DatabaseConnection();
    ~DatabaseConnection();

private:
    pqxx::connection m_Connection;

public:

};