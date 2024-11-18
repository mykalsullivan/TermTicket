//
// Created by msullivan on 11/18/24.
//

#include "Client.h"
#include <string>
#include <bits/getopt_core.h>

Client::Client(int argc, char *argv[])
{
    std::string username;
    std::string password;
    std::string hostname;
    int port;

    while (c = getopt(argc, argv, "u:w:h:p:"))
    {
        switch (c)
        {
            case 'u':

                break;
            case 'p':

                break;
            case 'h':

                break;
            case 'P':

                break;
            case '?':
            case 'h':

                break;
            default:
                break;
        }
    }


}

Client::~Client()
{

}

int Client::run()
{



    return 0;
}

void Client::exit()
{

}