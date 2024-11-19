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
        src/Client.h
        src/Client.cpp
        src/Ticket.h
        src/DatabaseConnection.cpp
        src/DatabaseConnection.h
        src/User.h
)

# Link the libraries
target_link_libraries(TermTicket
        ${PQXX_LIBRARIES}
)