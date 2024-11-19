//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <string>
#include <cassert>

// Forward declaration(s)
class DatabaseConnection;

struct CommandLineArgs {
    int argc = 0;
    char **argv;

    const char *operator[](int n) const
    {
        assert(n >= 0 && n < argc && "Out of bounds");
        return argv[n];
    }
};

struct LoginCredentials {
    std::string username;
    std::string password; // Will need to be hashed for security
};

class Client {
public:
    Client(int argc, char **argv);
    ~Client();

private:
    bool m_Running;
    CommandLineArgs m_Args;
    DatabaseConnection *m_TicketManager;
    LoginCredentials m_Credentials;

public:
    int run();
    void exit();

    /* Tickets */
    void addTicket();
    void deleteTicket();
    void modifyTicket();
    void mergeTicket();
    void takeTicket();
    void assignTicketToUser();
    void assignTicketToTeam();
    void listAssignedTickets();
    void listAllTickets();
    void viewTicket();
    void viewAssignedTickets();
    void viewAllTickets();
    [[nodiscard]] size_t getAssignedTicketCount();
    [[nodiscard]] size_t getOverallTicketCount();

    /* Users */
    void login();
    void logout();
    void registerUser();
    void deleteUser();
    void modifyUser();
    void setPassword();
    void listUsers();
    void viewUsers();
    [[nodiscard]] size_t getUserCount();

    /* Utilities/debugging */
    void resetDatabase();

private:
    DatabaseConnection *setupTicketManager();
    void handleInput(const std::string& input);
    [[nodiscard]] std::string parseConfigFile(const std::string &filename);
    [[nodiscard]] bool loadConfig(const std::string &config);
};