//
// Created by msullivan on 7/8/24.
//

#include "Client.h"

int main(int argc, char* argv[])
{
    auto app = new Client(argc, argv);
    return app->run();
}