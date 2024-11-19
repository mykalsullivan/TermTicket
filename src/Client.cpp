//
// Created by msullivan on 11/18/24.
//

#include "Client.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <unistd.h>

#define V_MAJ 0
#define V_MIN 0
#define V_REV 0

#define NO_IMPL std::cout << "Not currently implemented\n";

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

DatabaseConnection *Client::setupTicketManager()
{
    std::string hostname;
    int port = -1;

    int c;
    while ((c = getopt(m_Args.argc, m_Args.argv, ":u:p:H:P:h")) != -1)
        switch (c)
        {
            case 'u':
                m_Credentials.username = optarg;
            break;
            case 'p':
                m_Credentials.password = optarg;
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
    if (m_Credentials.username.empty())
    {
        std::cout << "Username: ";
        std::getline(std::cin, input);
        m_Credentials.username = input;
    }
    if (m_Credentials.password.empty())
    {
        std::cout << "Password: ";
        std::getline(std::cin, input);
        m_Credentials.password = input;
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

    return new DatabaseConnection(m_Credentials.username, m_Credentials.password, hostname, port);
}

void Client::handleInput(const std::string& input)
{
    if (input.empty())
        return;
    else if (input == "exit" || input == "stop" || input == "quit")
        exit();
    else if (input == "add ticket")
        addTicket();
    else if (input == "delete ticket")
        deleteTicket();
    else if (input == "modify ticket")
        modifyTicket();
    else if (input == "merge ticket")
        mergeTicket();
    else if (input == "take ticket")
        takeTicket();
    else if (input == "assign ticket to user")
        assignTicketToUser();
    else if (input == "assign ticket to team")
        assignTicketToTeam();
    else if (input == "list assigned tickets")
        listAssignedTickets();
    else if (input == "list all tickets")
        listAllTickets();
    else if (input == "view ticket")
        viewTicket();
    else if (input == "view assigned tickets")
        viewAssignedTickets();
    else if (input == "view all tickets")
        viewAllTickets();
    else if (input == "assigned ticket count")
        std::cout << std::to_string(getAssignedTicketCount()) << '\n';
    else if (input == "overall ticket count")
        std::cout << std::to_string(getOverallTicketCount()) << '\n';
    else if (input == "login")
        login();
    else if (input == "logout")
        logout();
    else if (input == "register user")
        registerUser();
    else if (input == "delete user")
        deleteUser();
    else if (input == "modify user")
        modifyUser();
    else if (input == "set password")
        setPassword();
    else if (input == "list users")
        listUsers();
    else if (input == "view users")
        viewUsers();
    else if (input == "reset")
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
    size_t ticketCount = getOverallTicketCount();
    if (ticketCount <= 0)
    {
        std::cout << "There are no tickets to delete\n";
        return;
    }

    listAllTickets();
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
    NO_IMPL;
}

void Client::takeTicket()
{
    NO_IMPL;
}

void Client::assignTicketToUser()
{
    NO_IMPL;
}

void Client::assignTicketToTeam()
{
    NO_IMPL;
}

void Client::listAssignedTickets()
{
    NO_IMPL;
}

void Client::listAllTickets()
{
    std::vector<Ticket> tickets = m_TicketManager->getTickets();
    for (const auto &ticket : tickets)
        std::cout << ticket.ticketID << ": \"" << ticket.title << "\"\n";
}


void Client::viewTicket()
{
    NO_IMPL;
}

void Client::viewAssignedTickets()
{
    // For now, this only shows all tickets. It should eventually query tickets assigned to the current user.
    NO_IMPL;
    listAllTickets();
}

void Client::viewAllTickets()
{
    std::vector<Ticket> tickets = m_TicketManager->getTickets();
    for (const auto &ticket : tickets)
        std::cout << ticket.ticketID << ": \"" << ticket.title << "\"\n"
                  << " -- Author: " << ticket.author << '\n'
                  << " -- Created: " << ticket.createdAt << '\n'
                  << " -- Modified: " << ticket.lastUpdatedAt << '\n'
                  << " -- Assigned to: " << (ticket.assignedTo) << '\n'
                  << " -- Priority: \"" << ticket.priority << "\"\n"
                  << " -- Status: \"" << ticket.status << "\"\n\n";
}

size_t Client::getAssignedTicketCount()
{
    NO_IMPL;
    return -1;
}

size_t Client::getOverallTicketCount()
{
    return m_TicketManager->getTickets().size();
}

void Client::login()
{
    NO_IMPL;
}

void Client::logout()
{
    NO_IMPL;
}

void Client::registerUser()
{
    NO_IMPL;
}

void Client::deleteUser()
{
    NO_IMPL;
}

void Client::modifyUser()
{
    NO_IMPL;
}


void Client::setPassword()
{
    NO_IMPL;
}

void Client::listUsers()
{
    NO_IMPL;
}


void Client::viewUsers()
{
    NO_IMPL;
}

size_t Client::getUserCount()
{
    NO_IMPL;
    return -1;
}


void Client::resetDatabase()
{
    if (m_TicketManager->resetDatabase())
        std::cout << "Successfully reset the ticket database\n";
    else
        std::cerr << "Failed to reset the ticket database\n";
}
