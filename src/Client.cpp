//
// Created by msullivan on 11/18/24.
//

#include "Client.h"
#include "TicketManager.h"
#include <string>
#include <bits/getopt_core.h>

void printHelpMenu()
{

}

Client::Client(int argc, char **argv)
{
    m_Args.argc = argc;
    m_Args.argv = argv;
}

Client::~Client()
{
    if (m_TicketManager != nullptr)
        delete m_TicketManager;
}

int Client::run()
{
    /* 1. Set up connection */
    m_TicketManager = setupTicketManager();

    /* 2. */
    while (m_Running)
    {

    }

    return 0;
}

void Client::exit()
{
    m_Running = false;
}

TicketManager *Client::setupTicketManager()
{
    std::string username;
    std::string password;
    std::string hostname;
    int port;

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
}
