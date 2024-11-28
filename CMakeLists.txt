cmake_minimum_required(VERSION 3.25)
project(TermTicket)

set(CMAKE_CXX_STANDARD 14)

# Find and link libpqxx (and libpq)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Include the directories for libpqxx
include_directories(${PQXX_INCLUDE_DIRS})

# Create executable
add_executable(TermTicket
        src/main.cpp
        src/OldClient.h
        src/OldClient.cpp
        src/Ticket.h
        src/server/db/DatabaseConnection.cpp
        src/server/db/DatabaseConnection.h
        src/User.h
        src/server/db/UserManager.h
        src/server/db/UserManager.cpp
        src/server/db/TicketManager.h
        src/server/db/TicketManager.cpp
        src/server/db/AuthenticationManager.h
        src/server/db/AuthenticationManager.cpp
        src/server/db/QueryManager.h
        src/server/db/QueryManager.cpp
        src/client/Client.h
        src/client/Client.cpp
        src/Connection.h
        src/Connection.cpp
        src/server/Server.h
        src/server/Server.cpp
)

# Link the libraries
target_link_libraries(TermTicket
        ${PQXX_LIBRARIES}
)