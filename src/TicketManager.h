//
// Created by msullivan on 11/18/24.
//

#pragma once
#include "Ticket.h"
#include <vector>
#include <pqxx/pqxx>

class TicketManager {
public:
    TicketManager(std::string username, std::string password, std::string host, int port);
    ~TicketManager();

private:
    pqxx::connection *m_DatabaseConnection;

public:
    // Tickets
    bool addTicket(Ticket ticket);
    bool deleteTicket(int ticketID);
    bool editTicket(int ticketID, Ticket ticket);
    bool mergeTicket(int sourceTicketID, int targetTicketID);
    Ticket getTicket(int ticketID);
    std::vector<Ticket> getTickets();

    // Comments
    bool addComment(int ticketID, TicketComment comment);
    bool deleteComment(int commentID);
    bool editComment(int commentID, TicketComment comment);
    TicketComment getComment(int commentID);
    std::vector<TicketComment> getComments(int ticketID);
};