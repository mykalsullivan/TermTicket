//
// Created by msullivan on 11/18/24.
//

#include "DatabaseConnection.h"
#include <iostream>
#include <fstream>
#include <sstream>

DatabaseConnection::DatabaseConnection(
    const std::string &username, const std::string &password,
    const std::string &host, int port) : m_Authenticated(false)
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


/* Comments */
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

/* Users */
bool DatabaseConnection::addUser(const User &user)
{

    return false;
}

bool DatabaseConnection::deleteUser(int userID)
{

    return false;
}

bool DatabaseConnection::editUser(int userID, const User &user)
{

    return false;
}

User DatabaseConnection::getUser(int userID)
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

std::vector<User> DatabaseConnection::getUsers()
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

bool DatabaseConnection::authenticate(const std::string &username, const std::string &password)
{
    pqxx::work work(*m_DatabaseConnection);
    std::string query = "SELECT password_hash "
                        "FROM users "
                        "WHERE username = $1";    // Will need to create an authenticate routine or function
    pqxx::result result;

    try
    {
        result = work.exec_params(query, username);
        work.commit();

        if (!result.empty())
            if (password == result[0]["password_hash"].as<std::string>())
            {
                m_Authenticated = true;
                return true;
            }
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return false;
    }
}

// This function is stupid and shouldn't exist
void DatabaseConnection::unauthenticate()
{
    m_Authenticated = false;
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
