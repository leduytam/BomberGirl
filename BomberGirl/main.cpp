#include <iostream>
#include "game.h"

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    Bombergirl::Game().run();

    return EXIT_SUCCESS;
}