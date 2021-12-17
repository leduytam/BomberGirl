#include <iostream>
#include "game.h"

int main()
{
    srand(time(NULL));
    Bombergirl::Game().run();

    return EXIT_SUCCESS;
}