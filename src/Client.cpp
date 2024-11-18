//
// Created by msullivan on 11/18/24.
//

#include "Client.h"
#include "TicketManager.h"
#include <iostream>
#include <bits/getopt_core.h>

#define V_MAJ 0
#define V_MIN 0
#define V_REV 0

void printHelpMenu()
{

}

Client::Client(int argc, char **argv) : m_Running(true), m_TicketManager(nullptr)
{
    m_Args.argc = argc;
    m_Args.argv = argv;
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

    while (int c = getopt(m_Args.argc, m_Args.argv, "u:w:h:p:"))
    {
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
    else
        std::cerr << "Unrecognized input \"" << input << "\"\n";
}

int Client::run()
{
    std::cout << "TermTicket v" << V_MAJ << '.' << V_MIN << '.' << V_REV << '\n';

    /* 1. Set up connection */
    m_TicketManager = setupTicketManager();

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

void Client::addTicket()
{

}

void Client::deleteTicket()
{

}

void Client::modifyTicket()
{

}

void Client::mergeTicket()
{

}

void Client::viewTicket()
{

}

void Client::viewAssignedTickets()
{

}

void Client::viewAllTickets()
{

}

void Client::exit()
{
    m_Running = false;
}