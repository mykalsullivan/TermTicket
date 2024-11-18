cmake_minimum_required(VERSION 3.28)
project(TermTicket)

set(CMAKE_CXX_STANDARD 14)

add_executable(TermTicket
        ### Core ###
        src/main.cpp
        src/Client.h
        src/Client.cpp
        src/Ticket.h
        src/TicketManager.cpp
        src/TicketManager.h

        ### Application ###

)