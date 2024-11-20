//
// Created by msullivan on 11/18/24.
//

#pragma once
#include "Ticket.h"
#include "User.h"
#include <vector>
#include <pqxx/pqxx>

class DatabaseConnection {
public:
    DatabaseConnection(const std::string& username, const std::string& password, const std::string& host, int port);
    ~DatabaseConnection();

private:
    pqxx::connection *m_DatabaseConnection;

public:
    /* Tickets */
    bool addTicket(const Ticket& ticket);
    bool deleteTicket(int ticketID) const;
    bool editTicket(int ticketID, const Ticket& ticket);
    bool mergeTicket(int sourceTicketID, int targetTicketID);
    [[nodiscard]] Ticket getTicket(int ticketID);
    std::vector<Ticket> getTickets();

    /* Comments */
    bool addComment(int ticketID, const Comment& comment);
    bool deleteComment(int commentID);
    bool editComment(int commentID, const Comment& comment);
    Comment getComment(int commentID);
    std::vector<Comment> getComments(int ticketID);

    /* Users */
    bool addUser(const User &user);
    bool deleteUser(int userID);
    bool editUser(int userID, const User &user);
    User getUser(int userID);
    std::vector<User> getUsers();

    /* Teams */
    bool addUserToTeam(int userID, int teamID);
    bool removeUserFromTeam(int userID, int teamID);
    std::vector<User> getUsersFromTeam(int teamID);
    std::vector<Team> getTeams();

    /* Utilities/debugging */
    bool authenticate(const std::string &username, const std::string &password) const;
    bool resetDatabase() const;

private:
    [[nodiscard]] static std::string getQueryFromFile(const std::string &filename);
};