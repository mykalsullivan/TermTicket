//
// Created by msullivan on 7/8/24.
//

#include "OldClient.h"

int main(int argc, char* argv[])
{
    auto app = new OldClient(argc, argv);
    return app->run();
}