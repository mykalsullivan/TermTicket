//
// Created by msullivan on 11/18/24.
//

#include "TicketManager.h"

TicketManager::TicketManager()
{
    m_DatabaseConnection = new pqxx::connection();

    if (m_DatabaseConnection != nullptr) {
        m_DatabaseConnection
    }
}

TicketManager::~TicketManager()
{

}

bool TicketManager::addTicket(Ticket ticket)
{

    return true;
}

bool TicketManager::deleteTicket(int ID)
{

    return true;
}

bool TicketManager::editTicket(int ID)
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

}
