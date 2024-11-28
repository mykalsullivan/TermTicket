//
// Created by msullivan on 11/27/24.
//

#pragma once
#include "DatabaseConnection.h"
#include "../../Ticket.h"

class TicketManager {
public:
    explicit TicketManager(DatabaseConnection &connection);
    ~TicketManager();

private:
    DatabaseConnection &m_Connection;

public:
    /* Tickets */
    bool addTicket(const Ticket &ticket);
    bool deleteTicket(int ticketID) const;
    bool editTicket(int ticketID, const Ticket& ticket);
    bool mergeTicket(int sourceTicketID, int targetTicketID);
    [[nodiscard]] Ticket getTicket(int ticketID);
    std::vector<Ticket> tickets();

    /* Comments */
    bool addComment(int ticketID, const Comment &comment);
    bool deleteComment(int commentID);
    bool editComment(int commentID, const Comment &comment);
    [[nodiscard]] Comment getComment(int commentID);
    std::vector<Comment> comments(int ticketID);
};