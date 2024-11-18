//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <string>
#include <cassert>
#include <pqxx/pqxx>

// Forward declaration(s)
class TicketManager;

struct CommandLineArgs {
    int argc = 0;
    char **argv;

    const char *operator[](int n) const
    {
        assert(n >= 0 && n < argc && "Out of bounds");
        return argv[n];
    }
};

class Client {
public:
    Client(int argc, char **argv);
    ~Client();

private:
    bool m_Running = false;
    CommandLineArgs m_Args;
    TicketManager *m_TicketManager;

public:
    int run();
    void exit();

private:
    TicketManager *setupTicketManager();
};