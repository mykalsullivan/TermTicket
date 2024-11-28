//
// Created by msullivan on 11/27/24.
//

#pragma once
#include <string>
#include <arpa/inet.h>

class Connection {
public:
    Connection() = default;
    ~Connection() = default;

private:
    int m_FD;
    sockaddr_in m_Address;

public:
    bool createSocket();
    void setSocket(int fd);
    [[nodiscard]] int getSocket() const { return m_FD; }
    virtual void setAddress(sockaddr_in address);
    [[nodiscard]] sockaddr_in &getAddress() { return m_Address; }
    [[nodiscard]] std::string getIP() const;
    [[nodiscard]] int getPort() const;

    void setNonBlocking() const;
    void setBlocking() const;
    void enableKeepalive() const;


    [[nodiscard]] bool sendMessage(const std::string &message) const;
    [[nodiscard]] std::string receiveMessage();
    [[nodiscard]] bool isValid() const;
    [[nodiscard]] bool isInactive() const;
};