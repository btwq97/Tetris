#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "ResourceManager.h"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
    TextureManager(): ResourceManager("textures.txt") {}

    sf::Texture* Load(const std::string& fileName)
    {
        sf::Texture* text = new sf::Texture(); //allocate memory on heap

        //if load fails just delete allocated memory and reset it to NULL.
        if (!text->loadFromFile(fileName))
        {
            delete text;
            text = NULL;
            std::cerr << "failed to load texture" << std::endl;
        }

        //otherwise return the texture
        return text;
    }
};