#include "MenuState.h"

const char* FONT_PATH = "Font/evil-empire-font/EvilEmpire-4BBVK.ttf";
const char* START_MUSIC = "Audio/start.wav";

MenuState::MenuState(Game* game)
{
    menuScreen.AddResource("MenuImage"); // Enter Image Name
    menuSprite.setTexture(*(menuScreen.GetResource("MenuImage")));
    
    // Game Text Menu
    font.loadFromFile(FONT_PATH);
    text.setFont(font);
    text.setPosition(100, 300);
    text.setCharacterSize(24); // in pixels, not points!                         
    text.setFillColor(sf::Color::White);   // set the color  
    text.setStyle(sf::Text::Bold); // set the text style

    //set positions of buttons
    for (int i = 0; i < NUM_BUTTONS; ++i)
    {
        buttons.push_back(text);
        buttons[i].setPosition(text.getPosition().x, text.getPosition().y + i * 100); // Spaces of 100, 200 in y-axis
    }
    buttons[0].setString("Play Game");
    buttons[1].setString("Quit Game");

    // Scaling image to appropiate size
    // Errors here
    sf::Vector2f targetSize(MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);
    menuSprite.setScale(targetSize.x / menuSprite.getLocalBounds().width,
        targetSize.y / menuSprite.getLocalBounds().height);

    // Audio
    start_buffer.loadFromFile(START_MUSIC);
    start_sound.setBuffer(start_buffer);
   
    this->game = game; // Pushing MenuState as current state
}

void MenuState::handleInput()
{
    sf::Event event;

    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {
        /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;

        /* Change Between game states */
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) // ESC button
                game->window.close();
            else if (event.key.code == sf::Keyboard::Return) // Enter button
                loadgame();
            break;
        //check if text is hovered over
        case sf::Event::MouseMoved:
            if (isTextClicked(buttons[0]))
                buttons[0].setFillColor(sf::Color::Red);
            else
                buttons[0].setFillColor(sf::Color::White);
            if (isTextClicked(buttons[1]))
                buttons[1].setFillColor(sf::Color::Red);
            else
                buttons[1].setFillColor(sf::Color::White);
            break;
        default:
            break;
        }
        //check if text is clicked.
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (isTextClicked(buttons[0]))
                loadgame();
            else if (isTextClicked(buttons[1]))
                game->window.close();
        }
    }
}

void MenuState::update(const float dt)
{
    

}

void MenuState::draw(const float dt)
{
    game->window.draw(menuSprite);

    //draw text
    for (auto x : buttons)
        game->window.draw(x);
}

void MenuState::loadgame()
{
    start_sound.play();
    game->pushState(new PlayState(game));
}

bool MenuState::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height); // Set a rectangle around text

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;

    //Otherwise, don't do anything
    return false;
}