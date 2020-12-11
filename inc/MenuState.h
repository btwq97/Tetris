#pragma once

#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "GameState.h"
#include "PlayState.h"
#include "TextureManager.h"

const float MENU_WINDOW_WIDTH = 320.f, MENU_WINDOW_HEIGHT = 420.f;

class MenuState : public GameState
{
public:
    MenuState(Game* game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

private:
    // Sprites
    sf::View view;
    TextureManager menuScreen;
    sf::Sprite menuSprite;

    // Audio
    sf::SoundBuffer start_buffer;
    sf::Sound start_sound;

    // For my buttons
    sf::Text text;
    std::vector<sf::Text> buttons;
    sf::Font font;
    const int NUM_BUTTONS = 2;
    bool isTextClicked(sf::Text text);

    // Push into PlayState
    void loadgame();
};

#endif /* GAME_STATE_START_HPP */