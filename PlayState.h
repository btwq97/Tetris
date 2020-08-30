#pragma once
#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "TextureManager.h"

const int TETRINOS_WIDTH = 18, TETRINOS_HEIGHT = 18, FACTOR = 18, RELEASE_POINT = 0;
const float PLAY_WINDOW_WIDTH = 320.f, PLAY_WINDOW_HEIGHT = 420.f, DELAY = 0.9, SPEED_UP = 0.05;

//Playing field
const int M = 20, N = 10; 

// Enum
enum class GAME_STATE
{
    GAME_OVER,
    GAME_IN_PROGRESS
};

class PlayState : public GameState
{
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    PlayState(Game* game);

private:
    bool rotate = 0;
    int dx = RELEASE_POINT, colournum = 1 + rand() % 7, n = rand() % 7; // tile pieces
    double timer = 0, delay = DELAY;


    TextureManager Background, Tetrinos, Frame;
    sf::Sprite sBackground, sTetrinos, sFrame;

    void PauseGame();
    bool Check();
    void is_complete();
    GAME_STATE GameOver();
};

#endif /* GAME_STATE_EDITOR_HPP */