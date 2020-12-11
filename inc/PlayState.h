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

    void PauseGame();
    bool Check();
    void is_complete();
    void game_over_state();
    void play_sound();
    GAME_STATE GameOver();
};

#endif /* GAME_STATE_EDITOR_HPP */