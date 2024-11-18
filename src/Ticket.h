//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <string>

struct Ticket {
    int ticketID;
    std::string title;
    std::string status;
    std::string priority;
    std::string createdAt;
    std::string lastModifiedAt;
    std::string assignedTo;
};

struct TicketComment {
    int ticketID;
    int commentID;
    std::string text;
    std::string createdAt;
    std::string lastModifiedAt;
    std::string sender;
};