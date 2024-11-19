//
// Created by msullivan on 11/18/24.
//

#pragma once
#include <string>

struct Ticket {
    int ticketID;
    std::string author;
    std::string createdAt;
    std::string lastUpdatedAt;
    std::string title;
    std::string status;
    std::string priority;
    std::string assignedTo;
};

struct TicketComment {
    int ticketID;
    int commentID;
    std::string author;
    std::string createdAt;
    std::string lastModifiedAt;
    std::string text;
};