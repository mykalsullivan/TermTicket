//
// Created by msullivan on 11/27/24.
//

#pragma once
#include <atomic>

class Server {
public:
    Server();
    ~Server();

private:
    std::atomic<bool> m_Running;

public:
    int run();
    void stop();
};

Server::Server() : m_Running(true)
{

}

Server::~Server()
{

}

int Server::run()
{
    while (m_Running)
    {

    }
}

void Server::stop()
{

}