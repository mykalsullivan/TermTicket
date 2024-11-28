//
// Created by msullivan on 11/27/24.
//

#include "QueryManager.h"
#include <fstream>
#include <iostream>

QueryManager::QueryManager(DatabaseConnection &connection) : m_Connection(connection)
{}

QueryManager::~QueryManager()
{}

bool QueryManager::connect(const std::string &connectionString)
{
    m_DatabaseConnection = new pqxx::connection(connectionString);

    if (!m_DatabaseConnection->is_open())
    {
        std::cerr << "Failed to connect to database\n";
        return false;
    }
    return true;
}

void QueryManager::disconnect() const
{
    m_DatabaseConnection->disconnect();
}

pqxx::result QueryManager::executeQuery(const std::string &query)
{
    pqxx::work work(*m_DatabaseConnection);
    pqxx::result result;
    try
    {
        result = work.exec(query);
        work.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
    }
    return result;
}

std::string QueryManager::getQueryFromFile(const std::string &filename)
{
    // 1. Open file
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        std::cerr << "Failed to open query file \"" << filename << "\"\n";
        return "";
    }

    // 2. Read and return file contents
    std::stringstream ss;
    ss << infile.rdbuf();
    return ss.str();
}
