#include "GameOverState.h"

extern const char* START_MUSIC;
extern const char* FONT_PATH;

GameOverState::GameOverState(Game* game)
{
    GameOverScreen.AddResource("GameOverImage");
    GameOverSprite.setTexture(*(GameOverScreen.GetResource("GameOverImage")));

    // Load Restart Audio
    restart_buffer.loadFromFile(START_MUSIC);
    restart_sound.setBuffer(restart_buffer);

    // Game Text Menu
    font.loadFromFile(FONT_PATH);
    text.setFont(font);
    text.setPosition(120, 310);
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);   // set the color  
    text.setStyle(sf::Text::Bold); // set the text style

    //set positions of things
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons.push_back(text);
        buttons[i].setPosition(text.getPosition().x, text.getPosition().y + i * 100); // Spaces of 100, 200 in y-axis
    }
    buttons[0].setString("Retry");
    buttons[1].setString("Exit");

    // Scaling image to appropiate size
    sf::Vector2f targetSize(MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);
    GameOverSprite.setScale(targetSize.x / GameOverSprite.getLocalBounds().width, targetSize.y / GameOverSprite.getLocalBounds().height);

	this->game = game;
}

void GameOverState::draw(const float dt)
{
    game->window.draw(GameOverSprite);

    //draw text
    for (auto x : buttons)
        game->window.draw(x);
}

void GameOverState::update(const float dt)
{
    
}

void GameOverState::handleInput()
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
            if (event.key.code == sf::Keyboard::Return)
                restart_game();
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
                restart_game();
            else if (isTextClicked(buttons[1]))
                game->window.close();
        }
    }
    
}

bool GameOverState::isTextClicked(sf::Text text)
{
    sf::IntRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height); // Set a rectangle around text

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(game->window)))
        return true;

    //Otherwise, don't do anything
    return false;
}

void GameOverState::restart_game()
{
    restart_sound.play();
    game->pushState(new PlayState(game));
}

