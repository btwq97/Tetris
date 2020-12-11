#pragma once
#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameState.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "TextureManager.h"

const int TETRINOS_WIDTH = 18, TETRINOS_HEIGHT = 18, FACTOR = 18;
const float PLAY_WINDOW_WIDTH = 320.f, PLAY_WINDOW_HEIGHT = 480.f, DELAY = 0.2, SPEED_UP = 0.05;

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
    int field[M][N] = { 0 };

    // swap between 2 frames to give illusion of moving
    struct position
    {int x=0, y=0;};

    // tetris pieces
    int tetrinos[7][4] =
    {
        1,3,5,7, // i
        2,4,5,7, // z
        3,5,4,6, // s
        3,5,4,7, // t
        2,3,5,7, // l
        3,5,7,6, // j
        2,3,4,5, // o
    };

    bool rotate = 0;
    int dx = 0, colournum = 1 + rand() % 7, n = rand() % 7; // tile pieces
    double timer = 0, delay = DELAY;

    // Sprites
    TextureManager Background, Frame, Tetrinos;
    sf::Sprite sBackground, sTetrinos, sFrame;

    // Audio
    sf::SoundBuffer press_buffer, gm_over_buffer, cmplt_buffer;
    sf::Sound press_sound, gm_over_sound, cmplt_sound;

    // Text
    sf::Text text;
    sf::Font font;

    // Init position
    position frame_a[4], frame_b[4];

    void PauseGame();
    bool Check();
    void is_complete();
    void game_over_state();
    void play_sound();
    GAME_STATE GameOver();
};

#endif /* GAME_STATE_EDITOR_HPP */