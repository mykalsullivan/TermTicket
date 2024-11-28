//
// Created by msullivan on 11/27/24.
//

#pragma once

class Client {
public:
    Client();
    ~Client();

private:
    bool m_Running;

public:
    int run();
    void stop();
};

Client::Client()
{

}

Client::~Client()
{

}

int Client::run()
{
    while (m_Running)
    {

    }
}

void Client::stop()
{
    m_Running = false;
}