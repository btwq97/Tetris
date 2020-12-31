#pragma once

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Game.h"

class Game;

class GameState
{
/*
    Protected allows the game pointer to be accessed in every child class (just like public does), but we can't access it if the class is not a child (so Resource Manager can't access it for example)
*/
protected:
    Game* game;
public:
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
};

#endif /* GAME_STATE_HPP */