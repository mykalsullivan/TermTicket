//
// Created by msullivan on 11/18/24.
//

#pragma once
#include "Ticket.h"
#include <vector>
#include <pqxx/pqxx>

class TicketManager {
public:
    TicketManager(const std::string& username, const std::string& password, const std::string& host, int port);
    ~TicketManager();

private:
    pqxx::connection *m_DatabaseConnection;

public:
    // Tickets
    bool addTicket(const Ticket& ticket);
    bool deleteTicket(int ticketID) const;
    bool editTicket(int ticketID, const Ticket& ticket);
    bool mergeTicket(int sourceTicketID, int targetTicketID);
    [[nodiscard]] Ticket getTicket(int ticketID);
    std::vector<Ticket> getTickets();

    // Comments
    bool addComment(int ticketID, const TicketComment& comment);
    bool deleteComment(int commentID);
    bool editComment(int commentID, const TicketComment& comment);
    TicketComment getComment(int commentID);
    std::vector<TicketComment> getComments(int ticketID);

    // Debug
    bool resetDatabase() const;

private:
    [[nodiscard]] static std::string getQueryFromFile(const std::string &filename) ;
};