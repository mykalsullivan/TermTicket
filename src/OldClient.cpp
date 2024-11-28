//
// Created by msullivan on 11/18/24.
//

#include "OldClient.h"
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

OldClient::OldClient(int argc, char **argv) : m_Running(true), m_TicketManager(nullptr)
{
    m_Args.argc = argc;
    m_Args.argv = argv;

    std::cout << "TermTicket v" << V_MAJ << '.' << V_MIN << '.' << V_REV << '\n';
}

OldClient::~OldClient()
{
    delete m_TicketManager;
}

DatabaseConnection *OldClient::setupTicketManager()
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

    if (username.empty())
    {
        std::cout << "Username: ";
        std::getline(std::cin, username);
    }
    if (password.empty())
    {
        std::cout << "Password: ";
        std::getline(std::cin, password);
    }
    if (hostname.empty())
    {
        std::cout << "Hostname: ";
        std::getline(std::cin, hostname);
    }
    if (port < 1000 || port >= 65535)
    {
        std::cout << "Port [1000-65535]: ";
        std::string input;
        std::getline(std::cin, input);
        port = std::stoi(input);
    }

    return new DatabaseConnection(username, password, hostname, port);
}

void OldClient::handleInput(const std::string& input)
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
    else if (input == "current user")
        currentUser();
    else if (input == "reset")
        resetDatabase();
    else
        std::cout << "Unrecognized input \"" << input << "\"\n";
}

std::string OldClient::parseConfigFile(const std::string &filename)
{
    NO_IMPL;
    return "";
}

bool OldClient::loadConfig(const std::string &config)
{
    NO_IMPL;
    return false;
}

bool OldClient::isAuthenticated() const
{
    // This is a terribly insecure way of checking if the user is authenticated. Move this to the DatabaseConnection
    if (m_TicketManager->isAuthenticated())
        return true;
    return false;
}


int OldClient::run()
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

void OldClient::exit()
{
    m_Running = false;
}

void OldClient::addTicket()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }

    Ticket ticket;

    // 1. Set the ticket title
    std::cout << "Title [blank to cancel]: ";
    std::getline(std::cin, ticket.title);
    if (ticket.title.empty()) return;

    // 2. Set the ticket status
    std::cout << "Status [blank to cancel]: ";
    std::getline(std::cin, ticket.status);
    if (ticket.title.empty()) return;

    // 3. Set the ticket priority
    std::cout << "Priority [blank to cancel]: ";
    std::getline(std::cin, ticket.priority);
    if (ticket.priority.empty()) return;

    // 4. Set the ticket author
    ticket.author = m_Credentials.username;

    // 5. Add the ticket to the database
    if (m_TicketManager->addTicket(ticket))
        std::cout << "Successfully created ticket\n";
    else
        std::cout << "Failed to create ticket\n";
}

void OldClient::deleteTicket()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }

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

void OldClient::modifyTicket()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::mergeTicket()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::takeTicket()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::assignTicketToUser()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::assignTicketToTeam()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::listAssignedTickets()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::listAllTickets()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }

    std::vector<Ticket> tickets = m_TicketManager->getTickets();
    for (const auto &ticket : tickets)
        std::cout << ticket.ticketID << ": \"" << ticket.title << "\"\n";
}


void OldClient::viewTicket()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::viewAssignedTickets()
{
    // For now, this only shows all tickets. It should eventually query tickets assigned to the current user.
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
    listAllTickets();
}

void OldClient::viewAllTickets()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }

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

size_t OldClient::getAssignedTicketCount()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return -1;
    }
    return -1;
}

size_t OldClient::getOverallTicketCount()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return -1;
    }
    return m_TicketManager->getTickets().size();
}

void OldClient::login()
{
    if (!m_Credentials.username.empty())
        std::cout << "Note: You are already logged in as \"" << m_Credentials.username << "\"\n";

    // 1. Prompt username
    std::string username;
    std::cout << "Username: ";
    std::getline(std::cin, username);

    // 2. Prompt password
    std::string password;
    std::cout << "Password (will eventually be hidden from terminal): ";
    std::getline(std::cin, password);

    // 3. Authenticate with the database
    if (m_TicketManager->authenticate(username, password))
    {
        std::cout << "Successfully authenticated as \"" + username + "\"\n";
        m_Credentials.username = username;
        return;
    }
    std::cout << "Failed to authenticate with those credentials\n";
}

void OldClient::logout()
{
    if (!isAuthenticated())
    {
        std::cout << "You are not currently logged in\n";
        return;
    }
    std::cout << "Logged out of account \"" << m_Credentials.username << "\"\n";
    m_Credentials.username = "";
    m_Credentials.password = "";
    m_TicketManager->unauthenticate();
}

void OldClient::registerUser()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::deleteUser()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::modifyUser()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}


void OldClient::setPassword()
{
    NO_IMPL;
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

void OldClient::listUsers()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
    std::vector<User> users = m_TicketManager->getUsers();

    std::cout << "--- Users ---\n";
    std::cout << "User(s): " << users.size() << '\n';
    for (int i = 0; i < users.size(); i++)
        std::cout << (i + 1) << ") " << users[i].username << '\n';
    std::cout << std::endl;
}


void OldClient::viewUsers()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return;
    }
}

size_t OldClient::getUserCount()
{
    if (!isAuthenticated())
    {
        std::cout << "You must login before performing this action\n";
        return -1;
    }
    return m_TicketManager->getUsers().size();
}

void OldClient::currentUser()
{
    if (!isAuthenticated())
    {
        std::cout << "You are not current logged in\n";
        return;
    }
    std::cout << "Current user: \"" << m_Credentials.username << "\"\n";
}


void OldClient::resetDatabase()
{
    if (m_TicketManager->resetDatabase())
        std::cout << "Successfully reset the ticket database\n";
    else
        std::cout << "Failed to reset the ticket database\n";
}
