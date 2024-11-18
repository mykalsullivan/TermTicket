//
// Created by msullivan on 11/18/24.
//

#include "TicketManager.h"
#include <iostream>

TicketManager::TicketManager(std::string username, std::string password, std::string host, int port)
{
    std::string connectionString = "dbname=term_ticket"
                                   " user=" + username +
                                   " password=" + password +
                                   " host=" + host +
                                   " port=" + std::to_string(port);
    m_DatabaseConnection = new pqxx::connection(connectionString);

    if (!m_DatabaseConnection->is_open()) {
        std::cerr << "Failed to connect to database\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Successfully connected to ticket database\n";
}

TicketManager::~TicketManager()
{
    m_DatabaseConnection->disconnect();
}

bool TicketManager::addTicket(Ticket ticket)
{

    return true;
}

bool TicketManager::deleteTicket(int ID)
{

    return true;
}

bool TicketManager::editTicket(int ID, Ticket ticket)
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
    pqxx::result result = work.exec("SELECT * FROM tickets;");

    std::vector<Ticket> tickets;

    for (const auto &row : result)
    {
        Ticket ticket;
        ticket.ticketID = row["ticket_id"].as<int>();
        ticket.title = row["ticket_title"].c_str();
        ticket.status = row["ticket_status"].c_str();
        ticket.priority = row["ticket_priority"].c_str();
        ticket.createdAt = row["ticket_created_at"].c_str();
        ticket.lastModifiedAt = row["ticket_last_modified_at"].c_str();
        ticket.assignedTo = row["ticket_assigned_to"].c_str();
        tickets.emplace_back(ticket);
    }
    return tickets;
}

bool TicketManager::addComment(int ticketID, TicketComment comment)
{

    return true;
}

bool TicketManager::deleteComment(int commentID)
{
    
    return true;
}

bool TicketManager::editComment(int commentID, TicketComment comment)
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
    pqxx::result result = work.exec("SELECT * FROM comments WHERE ticket_id = " + std::to_string(ticketID) + ';');

    std::vector<TicketComment> comments;

    for (const auto &row : result)
    {
        TicketComment comment;
        comment.commentID = row["comment_id"].as<int>();
        comment.commentID = row["comment_id"].as<int>();
        comment.text = row["comment_text"].c_str();
        comment.createdAt = row["comment_created_at"].c_str();
        comment.lastModifiedAt = row["comment_last_modified_at"].c_str();
        comment.sender = row["comment_sender"].c_str();
        comments.emplace_back(comment);
    }
    return comments;
}