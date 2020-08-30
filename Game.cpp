#include "Game.h"

const int WINDOW_HEIGHT = 420;
const int WINDOW_WIDTH = 320;
const int MAX_FPS = 60;
const char* WINDOW_TITLE = "My Tetris";

Game::Game()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);

    window.setFramerateLimit(MAX_FPS);
}

Game::~Game()
{
    while (!states.empty())
        popState();
}

void Game::pushState(GameState* state)
{
    states.push_back(state);
}

void Game::popState()
{
    states.back();
    delete states.back();
    states.pop_back();
}

GameState* Game::CurrentState()
{
    if (states.empty())
        return nullptr;
    else
        return states.back();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate (you can ignore this stuff for now)
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        if (CurrentState() == nullptr)
            continue;

        //get user input for current game state
        CurrentState()->handleInput();

        //update anything neccessary
        CurrentState()->update(dt);

        //clear window
        window.clear();

        //draw anything in the current game state
        CurrentState()->draw(dt);

        window.display();

        dt = 0; // Reset elapsed time
    }
}