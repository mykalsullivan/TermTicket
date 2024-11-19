//
// Created by msullivan on 11/18/24.
//

#include "Client.h"
#include "TicketManager.h"
#include <iostream>
#include <unistd.h>

#define V_MAJ 0
#define V_MIN 0
#define V_REV 0

void printHelpMenu()
{
    std::cout << "Valid usage:\n"
              << "-u <username> : Sets the username for authenticating with the ticket database\n"
              << "-p <password> : Sets the password for authenticating with the ticket database\n"
              << "-H <hostname> : Sets the hostname of the ticket database\n"
              << "-P <port> : Sets the port of the ticket database\n"
              << "-h : Displays this help menu\n";
}

Client::Client(int argc, char **argv) : m_Running(true), m_TicketManager(nullptr)
{
    m_Args.argc = argc;
    m_Args.argv = argv;

    std::cout << "TermTicket v" << V_MAJ << '.' << V_MIN << '.' << V_REV << '\n';
}

Client::~Client()
{
    delete m_TicketManager;
}

TicketManager *Client::setupTicketManager() const
{
    std::string username;
    std::string password;
    std::string hostname;
    int port = -1;

    int c;
    while ((c = getopt(m_Args.argc, m_Args.argv, ":u:p:H:P:h")) != -1)
        switch (c)
        {
            case 'u':
                username = optarg;
            break;
            case 'p':
                password = optarg;
            break;
            case 'H':
                hostname = optarg;
            break;
            case 'P':
                port = std::atoi(optarg);
            break;
            case '?':
            case 'h':
                printHelpMenu();
            return nullptr;
            default:
                printHelpMenu();
            return nullptr;
        }

    std::string input;
    if (username.empty())
    {
        std::cout << "Username: ";
        std::getline(std::cin, input);
        username = input;
    }
    if (password.empty())
    {
        std::cout << "Password: ";
        std::getline(std::cin, input);
        password = input;
    }
    if (hostname.empty())
    {
        std::cout << "Hostname: ";
        std::getline(std::cin, input);
        hostname = input;
    }
    if (port < 1000 || port >= 65535)
    {
        std::cout << "Port [1000-65535]: ";
        std::getline(std::cin, input);
        port = std::stoi(input);
    }

    return new TicketManager(username, password, hostname, port);
}

void Client::handleInput(const std::string& input)
{
    if (input.empty())
        return;
    else if (input == "exit" || input == "stop" || input == "quit")
        exit();
    else if (input == "add")
        addTicket();
    else if (input == "delete")
        deleteTicket();
    else if (input == "modify")
        modifyTicket();
    else if (input == "merge")
        mergeTicket();
    else if (input == "view")
        viewTicket();
    else if (input == "view assigned")
        viewAssignedTickets();
    else if (input == "view all")
        viewAllTickets();
    else if (input == "reset db")
        resetDatabase();
    else
        std::cerr << "Unrecognized input \"" << input << "\"\n";
}

int Client::run()
{
    /* 1. Set up connection */
    m_TicketManager = setupTicketManager();
    if (m_TicketManager == nullptr) return -1;

    /* 2. Get and handle user input */
    while (m_Running)
    {
        std::string input;
        std::cout << ":: ";
        std::getline(std::cin, input);
        handleInput(input);
    }
    return 0;
}

void Client::exit()
{
    m_Running = false;
}

void Client::addTicket()
{
    Ticket ticket;
    ticket.author = "msullivan"; // Temp

    std::cout << "Title [blank to cancel]: ";
    std::getline(std::cin, ticket.title);
    if (ticket.title.empty()) return;

    std::cout << "Status [blank to cancel]: ";
    std::getline(std::cin, ticket.status);
    if (ticket.title.empty()) return;

    std::cout << "Priority [blank to cancel]: ";
    std::getline(std::cin, ticket.priority);
    if (ticket.priority.empty()) return;

    if (m_TicketManager->addTicket(ticket))
        std::cout << "Successfully created ticket\n";
    else
        std::cerr << "Failed to create ticket\n";
}

void Client::deleteTicket()
{
    size_t ticketCount = listAllTickets();

    if (ticketCount <= 0)
    {
        std::cout << "There are no tickets to delete\n";
        return;
    }

    std::cout << "Target? [1-" << std::to_string(ticketCount) << "]: ";

    int selection = -1;
    std::cin >> selection;
    std::cin.ignore();

    // Will need exception handling
    m_TicketManager->deleteTicket(selection - 1);
}

void Client::modifyTicket()
{

}

void Client::mergeTicket()
{

}

size_t Client::listAllTickets()
{
    std::vector<Ticket> tickets = m_TicketManager->getTickets();

    if (tickets.empty())
        std::cout << "There are no tickets available to view\n";

    for (const auto &ticket : tickets)
        std::cout << ticket.ticketID << ": \"" << ticket.title << "\"\n";

    return tickets.size();
}


void Client::viewTicket()
{

}

size_t Client::viewAssignedTickets()
{
    std::vector<Ticket> tickets;
    return tickets.size();
}

size_t Client::viewAllTickets()
{
    std::vector<Ticket> tickets = m_TicketManager->getTickets();

    if (tickets.empty())
        std::cout << "There are no tickets available to view\n";

    for (const auto &ticket : tickets)
        std::cout << ticket.ticketID << ": \"" << ticket.title << "\"\n"
                  << " -- Author: " << ticket.author << '\n'
                  << " -- Created: " << ticket.createdAt << '\n'
                  << " -- Modified: " << ticket.lastUpdatedAt << '\n'
                  << " -- Assigned to: " << (ticket.assignedTo) << '\n'
                  << " -- Priority: \"" << ticket.priority << "\"\n"
                  << " -- Status: \"" << ticket.status << "\"\n\n";
    return tickets.size();
}

void Client::resetDatabase()
{
    if (m_TicketManager->resetDatabase())
        std::cout << "Successfully reset the ticket database\n";
    else
        std::cerr << "Failed to reset the ticket database\n";
}
