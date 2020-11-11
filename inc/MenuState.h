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

class MenuState : public GameState  //make GameState functions public to this class so we can derive it's functions.
{
public:
    //constructor (compiler will automatically make a default one)
    MenuState(Game* game);

    //the three functions are teh three things we must do.
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

private:
    //let's make a view for this just in case we want it
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

    //this will be used to change the game state to the "Play" state.
    void loadgame();
};

#endif /* GAME_STATE_START_HPP */