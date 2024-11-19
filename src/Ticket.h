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

struct Subtask {
    int subtaskID;
    int ticketID;
    std::string createdAt;
    std::string lastModifiedAt;
    std::string title;
    std::string status;
};

struct Comment {
    int ticketID;
    int commentID;
    std::string createdAt;
    std::string lastModifiedAt;
    std::string author;
    std::string text;
};

struct Deadline {
    int deadlineID;
    int ticketID;
    std::string createdAt;
    std::string lastUpdatedAt;
    std::string reason;
    bool isStrict;
};

struct SLA {
    int slaID;
    int responseTime;       // May have wrong type
    int resolutionTime;     // May have wrong type
    std::string description;
};