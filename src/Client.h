//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <string>
#include <pqxx/pqxx>

// Forward declaration(s)
class TicketManager;

class Client {
public:
    Client(int argc, char *argv[]);
    ~Client();

private:
    bool m_Running = false;
    TicketManager *m_TicketManager;

public:
    int run();
    void exit();
};