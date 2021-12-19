#include <iostream>
#include "game.h"

int main()
{
    srand(time(0));
    Bombergirl::Game().run();

    return EXIT_SUCCESS;
}