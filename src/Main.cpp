#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameOverState.h"

int main()
{
    Game game;

    game.pushState(new MenuState(&game));  //we want to create a pointer at the game objects address. this will enter our menu.

    game.gameLoop();

    return 0;
}

