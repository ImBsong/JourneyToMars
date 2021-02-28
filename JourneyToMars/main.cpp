#include "Game.h"

/*
    Simple space shooter game.  
    -Inspired by Raiden (https://en.wikipedia.org/wiki/Raiden_(video_game))

    Started this project by following various guides such as Suraj Sharma 
    - YT Link: https://www.youtube.com/channel/UC2i39AOpDSlO1Mrn1jQ8Xkg)

    Music thanks to https://patrickdearteaga.com/royalty-free-music/
*/

int main()
{
    //Initialize Random Seed
    srand(static_cast<unsigned>(time(0)));

    Game game;

    game.run();

    std::cin.get();

    return 0;
}