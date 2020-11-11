#pragma once

#ifndef GAME_STATE_OVER_HPP
#define GAME_STATE_OVER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "GameState.h"
#include "PlayState.h"
#include "TextureManager.h"

class GameOverState : public GameState
{
public:
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameOverState(Game* game);

private:
    // Sprites
    TextureManager GameOverScreen;
    sf::Sprite GameOverSprite;

    // Audio
    sf::SoundBuffer restart_buffer;
    sf::Sound restart_sound;

    // Text
    sf::Text text;
    std::vector<sf::Text> buttons;
    sf::Font font;
    const int NUM_BUTTONS = 2;
    bool isTextClicked(sf::Text text);

    void restart_game();
};


#endif /* GAME_STATE_OVER_HPP */