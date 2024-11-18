//
// Created by msullivan on 11/18/24.
//

#pragma once
#include "Ticket.h"
#include <vector>
#include <pqxx/pqxx>

class TicketManager {
public:
    TicketManager();
    ~TicketManager();

private:
    pqxx::connection *m_DatabaseConnection;

public:
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setHostname(std::string hostname);
    void setPort(int port);

    bool addTicket(Ticket ticket);
    bool deleteTicket(int ID);
    bool editTicket(int ID);
    bool mergeTicket(int sourceID, int targetID);
    Ticket getTicket(int ID);
    std::vector<Ticket> getTickets();


};