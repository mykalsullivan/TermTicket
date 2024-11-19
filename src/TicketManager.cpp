//
// Created by msullivan on 11/18/24.
//

#include "TicketManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

TicketManager::TicketManager(const std::string &username, const std::string &password, const std::string &host, int port)
{
    std::string connectionString = "dbname=term_ticket"
                                   " user=" + username +
                                   " password=" + password +
                                   " host=" + host +
                                   " port=" + std::to_string(port);
    m_DatabaseConnection = new pqxx::connection(connectionString);

    if (!m_DatabaseConnection->is_open())
    {
        std::cerr << "Failed to connect to database\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Successfully connected to ticket database\n";
}

TicketManager::~TicketManager()
{
    m_DatabaseConnection->disconnect();
}

bool TicketManager::addTicket(const Ticket &ticket)
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "INSERT INTO tickets "
                        "("
                            "title, author, status, priority, assigned_to"
                        ") "
                        "VALUES "
                        "("
                            "$1, $2, $3, $4, $5"
                        ");";
    try
    {
        work.exec_params(query, ticket.title, ticket.author, ticket.status, ticket.priority, "NULL");
        work.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return false;
    }
    return true;
}

bool TicketManager::deleteTicket(int id) const
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "DELETE FROM tickets "
                        "WHERE ticket_id = " + std::to_string(id) + ";";
    try
    {
        work.exec(query);
        work.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return false;
    }
    return true;
}

bool TicketManager::editTicket(int ID, const Ticket &ticket)
{

    return true;
}

bool TicketManager::mergeTicket(int sourceID, int targetID)
{

    return true;
}

Ticket TicketManager::getTicket(int ID)
{

    return {};
}

std::vector<Ticket> TicketManager::getTickets()
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "SELECT * FROM tickets;";
    pqxx::result result;
    try
    {
        result = work.exec(query);
        work.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return {};
    }

    std::vector<Ticket> tickets;

    for (const auto &row : result)
    {
        try
        {
            Ticket ticket;
            ticket.ticketID = row["ticket_id"].as<int>();
            ticket.createdAt = row["created_at"].as<std::string>();
            ticket.lastUpdatedAt = row["last_updated_at"].as<std::string>();
            ticket.author = row["author"].as<std::string>();
            ticket.title = row["title"].as<std::string>();
            ticket.status = row["status"].as<std::string>();
            ticket.priority = row["priority"].as<std::string>();
            ticket.assignedTo = row["assigned_to"].as<std::string>();
            tickets.emplace_back(ticket);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what();
        }
    }
    return tickets;
}

bool TicketManager::addComment(int ticketID, const TicketComment &comment)
{

    return true;
}

bool TicketManager::deleteComment(int commentID)
{
    
    return true;
}

bool TicketManager::editComment(int commentID, const TicketComment &comment)
{

    return true;
}

TicketComment TicketManager::getComment(int commentID)
{

    return {};
}

std::vector<TicketComment> TicketManager::getComments(int ticketID)
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "SELECT * FROM comments WHERE ticket_id = " + std::to_string(ticketID) + ';';
    pqxx::result result = work.exec(query);

    std::vector<TicketComment> comments;

    for (const auto &row : result)
    {
        TicketComment comment;
        comment.commentID = row["comment_id"].as<int>();
        comment.ticketID = row["ticket_id"].as<int>();
        comment.author = row["comment_author"].c_str();
        comment.createdAt = row["comment_created_at"].c_str();
        comment.lastModifiedAt = row["comment_last_modified_at"].c_str();
        comment.text = row["comment_text"].c_str();
        comments.emplace_back(comment);
    }
    return comments;
}

// This will need better exception handling
bool TicketManager::resetDatabase() const
{
    pqxx::work work(*m_DatabaseConnection);
    pqxx::result result;
    std::string query;
    try
    {
        // 1. Drop both the tickets and comments table if they exist
        query = getQueryFromFile("/home/msullivan/Development/GitHub/TermTix/sql/DropTables.sql");
        work.exec(query);

        // 2. Re-create the tickets table
        query = getQueryFromFile("/home/msullivan/Development/GitHub/TermTix/sql/CreateTicketsTable.sql");
        if (query.empty())
        {
            std::cerr << "Failed to create tickets table\n";
            return false;
        }
        work.exec(query);

        // 3. Re-create the comments table
        query = getQueryFromFile("/home/msullivan/Development/GitHub/TermTix/sql/CreateCommentsTable.sql");
        if (query.empty())
        {
            std::cerr << "Failed to create comments table\n";
            return false;
        }
        work.exec(query);

        // 4. Commit changes to the database
        work.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return false;
    }
    return true;
}

std::string TicketManager::getQueryFromFile(const std::string &filename)
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
