//
// Created by msullivan on 11/27/24.
//

#include "TicketManager.h"
#include "QueryManager.h"
#include <pqxx/pqxx>

TicketManager::TicketManager(DatabaseConnection &connection) : m_Connection(connection)
{}

TicketManager::~TicketManager() = default;

/* Tickets */
bool TicketManager::addTicket(const Ticket &ticket)
{
    std::string query = "INSERT INTO tickets "
                        "("
                            "created_at, "
                            "last_updated_at, "
                            "author, "
                            "title, "
                            "status, "
                            "priority, "
                            "assigned_to"
                        ") "
                        "VALUES "
                        "("
                            + ticket.createdAt + ", "
                            + ticket.lastUpdatedAt + ", "
                            + ticket.author + ", "
                            + ticket.title + ", "
                            + ticket.status + ", "
                            + ticket.priority + ", "
                            + ticket.assignedTo +
                        ");";
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);
    if (!result.empty()) return true;
    return false;
}

bool TicketManager::deleteTicket(int ticketID) const
{
    std::string query = "DELETE FROM tickets"
                        "WHERE ticket_id = " + ticketID + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);
    if (!result.empty()) return true;
    return false;
}

bool TicketManager::editTicket(int ticketID, const Ticket &ticket)
{
    std::string query = "UPDATE tickets "
                        "SET author = " + ticket.author + ", " +
                            "last_updated_at = NOW(), "
                            "title = " + ticket.title + ", "
                            "status = " + ticket.status + ", "
                            "priority = " + ticket.priority + ", "
                            "assigned_to = " + ticket.assignedTo +
                        "WHERE ticket_id = " + std::to_string(ticketID) + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);
    if (!result.empty()) return true;
    return false;
}

bool TicketManager::mergeTicket(int sourceTicketID, int targetTicketID)
{
    // This will be very involved and needs a bunch of other things to be set up before it will work
    return true;
}

Ticket TicketManager::getTicket(int ticketID)
{
    std::string query = "SELECT * FROM tickets"
                        "WHERE ticket_id = " + std::to_string(ticketID) + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);

    // Will need exception handling
    Ticket ticket {};
    if (!result.empty())
    {
        ticket.ticketID = ticketID;
        ticket.createdAt = result[0]["created_at"].as<std::string>();
        ticket.lastUpdatedAt = result[0]["last_updated_at"].as<std::string>();
        ticket.author = result[0]["author"].as<std::string>();
        ticket.title = result[0]["title"].as<std::string>();
        ticket.status = result[0]["status"].as<std::string>();
        ticket.priority = result[0]["priority"].as<std::string>();
        ticket.assignedTo = result[0]["assigned_to"].as<std::string>();
    }
    return ticket;
}

std::vector<Ticket> TicketManager::tickets()
{
    std::string query = "SELECT * FROM tickets;";
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);

    // Will need exception handling
    std::vector<Ticket> tickets;
    if (!result.empty())
    {
        for (const auto &row : result)
        {
            Ticket ticket {};
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
    }
    return tickets;
}

/* Comments */
bool TicketManager::addComment(int ticketID, const Comment &comment)
{
    std::string query = "INSERT INTO comments "
                        "("
                            "ticket_id, "
                            "created_at, "
                            "last_modified_at, "
                            "author, "
                            "text"
                        ") "
                        "VALUES "
                        "("
                            + std::to_string(ticketID) + ", "
                            + comment.createdAt + ", "
                            + comment.lastModifiedAt + ", "
                            + comment.author + ", "
                            + comment.text +
                        ");";
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);
    if (!result.empty()) return true;
    return false;
}

bool TicketManager::deleteComment(int commentID)
{
    std::string query = "DELETE FROM comments"
                        "WHERE comment_id = " + commentID + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);
    if (!result.empty()) return true;
    return false;
}

bool TicketManager::editComment(int commentID, const Comment &comment)
{
    std::string query = "UPDATE comments "
                        "SET ticket_id = " + std::to_string(comment.ticketID) + ", " +
                            "last_updated_at = NOW(), "
                            "author = " + comment.author + ", "
                            "text = " + comment.text +
                        "WHERE comment_id = " + std::to_string(commentID) + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);
    if (!result.empty()) return true;
    return false;
}

Comment TicketManager::getComment(int commentID)
{
    std::string query = "SELECT * FROM comments"
                        "WHERE comment_id = " + std::to_string(commentID) + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);

    // Will need exception handling
    Comment comment {};
    if (!result.empty())
    {
        comment.commentID = commentID;
        comment.ticketID = result[0]["ticket_id"].as<int>();
        comment.createdAt = result[0]["created_at"].as<std::string>();
        comment.lastModifiedAt = result[0]["last_modified_at"].as<std::string>();
        comment.author = result[0]["author"].as<std::string>();
        comment.text = result[0]["text"].as<std::string>();
    }
    return comment;
}

std::vector<Comment> TicketManager::comments(int ticketID)
{
    std::string query = "SELECT * FROM comments"
                        "WHERE ticket_id = " + std::to_string(ticketID) + ';';
    pqxx::result result = m_Connection.queryManager()->executeQuery(query);

    // Will need exception handling
    std::vector<Comment> comments;
    if (!result.empty())
    {
        for (const auto &row : result)
        {
            Comment comment {};
            comment.commentID = row["comment_id"].as<int>();
            comment.ticketID = result[0]["ticket_id"].as<int>();
            comment.createdAt = result[0]["created_at"].as<std::string>();
            comment.lastModifiedAt = result[0]["last_modified_at"].as<std::string>();
            comment.author = result[0]["author"].as<std::string>();
            comment.text = result[0]["text"].as<std::string>();
            comments.emplace_back(comment);
        }
    }
    return comments;
}