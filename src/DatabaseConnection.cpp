//
// Created by msullivan on 11/18/24.
//

#include "DatabaseConnection.h"
#include <iostream>
#include <fstream>
#include <sstream>

DatabaseConnection::DatabaseConnection(const std::string &username, const std::string &password, const std::string &host, int port)
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

DatabaseConnection::~DatabaseConnection()
{
    m_DatabaseConnection->disconnect();
}

bool DatabaseConnection::addTicket(const Ticket &ticket)
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

bool DatabaseConnection::deleteTicket(int id) const
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

bool DatabaseConnection::editTicket(int ID, const Ticket &ticket)
{

    return true;
}

bool DatabaseConnection::mergeTicket(int sourceID, int targetID)
{

    return true;
}

Ticket DatabaseConnection::getTicket(int ID)
{

    return {};
}

std::vector<Ticket> DatabaseConnection::getTickets()
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

bool DatabaseConnection::addComment(int ticketID, const Comment &comment)
{

    return true;
}

bool DatabaseConnection::deleteComment(int commentID)
{
    
    return true;
}

bool DatabaseConnection::editComment(int commentID, const Comment &comment)
{

    return true;
}

Comment DatabaseConnection::getComment(int commentID)
{

    return {};
}

std::vector<Comment> DatabaseConnection::getComments(int ticketID)
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "SELECT * FROM comments WHERE ticket_id = " + std::to_string(ticketID) + ';';
    pqxx::result result = work.exec(query);

    std::vector<Comment> comments;

    for (const auto &row : result)
    {
        Comment comment;
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
bool DatabaseConnection::resetDatabase() const
{
    pqxx::work work(*m_DatabaseConnection);

    std::string query = getQueryFromFile("/home/msullivan/Development/GitHub/TermTix/sql/ResetDatabase.sql");
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

std::string DatabaseConnection::getQueryFromFile(const std::string &filename)
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
