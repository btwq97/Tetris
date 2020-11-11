#include "PlayState.h"

//const char* PRESSED_MUSIC = "Audio/move.wav";
//const char* GM_OVER_MUSIC = "Audio/gameover.wav";
//const char* COMPLT_MUSIC = "Audio/complete.wav";
const char* PRESSED_MUSIC = "../Audio/move.wav";
const char* GM_OVER_MUSIC = "../Audio/gameover.wav";
const char* COMPLT_MUSIC = "../Audio/complete.wav";
extern const char* FONT_PATH;

PlayState::PlayState(Game* game)
{
    srand(time(NULL)); // Init rand seed

    // Loading all necessary Images
    Background.AddResource("TetrisBG"); // Enter Image Name
    sBackground.setTexture(*(Background.GetResource("TetrisBG")));
    Frame.AddResource("TetrisFrame"); // Enter Image Name
    sFrame.setTexture(*(Frame.GetResource("TetrisFrame")));
    Tetrinos.AddResource("Tetrinos"); // Enter Image Name
    sTetrinos.setTexture(*(Tetrinos.GetResource("Tetrinos")));

    sf::Vector2f targetSize(PLAY_WINDOW_WIDTH, PLAY_WINDOW_HEIGHT);
    sBackground.setScale(targetSize.x / sBackground.getLocalBounds().width, targetSize.y / sBackground.getLocalBounds().height);
    sFrame.setScale(targetSize.x / sFrame.getLocalBounds().width, targetSize.y / sFrame.getLocalBounds().height);

    // Audio
    press_buffer.loadFromFile(PRESSED_MUSIC);
    press_sound.setBuffer(press_buffer);

    gm_over_buffer.loadFromFile(GM_OVER_MUSIC);
    gm_over_sound.setBuffer(gm_over_buffer);

    cmplt_buffer.loadFromFile(COMPLT_MUSIC); // Find out which line does the elimintation of tetrinos
    cmplt_sound.setBuffer(cmplt_buffer);

    // Text
    font.loadFromFile(FONT_PATH);
    text.setFont(font);
    text.setPosition(10, 405);
    text.setCharacterSize(20); // in pixels, not points!                         
    text.setFillColor(sf::Color::Black);   // set the color  
    text.setString("Press ESC to quit.\nPress UP to rotate.\nPress LEFT/RIGHT to move.\n");

    this->game = game;
}

void PlayState::draw(const float dt)
{
    // Ranking matters

    // Background
    game->window.draw(sBackground);

    /*
        Figure out why Tetrinos does not want to show up
    */
    // Falling Tetrinos
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; j++)
        {
            if (field[i][j] != 0)
            {
                // getting the single cube from tiles.png
                sTetrinos.setTextureRect(sf::IntRect(field[i][j] * FACTOR, 0, TETRINOS_WIDTH, TETRINOS_HEIGHT));
                // to prevent conversion warning
                float float_i = (float)i;
                float float_j = (float)j;
                sTetrinos.setPosition(float_j * FACTOR, float_i * FACTOR);
                sTetrinos.move(28, 31); //offset to fit within frame
                game->window.draw(sTetrinos);
            }
        }
    }

    // Tetrinos at the bottom
    for (int i = 0; i < 4; ++i)
    {
        sTetrinos.setTextureRect(sf::IntRect(colournum * FACTOR, 0, TETRINOS_WIDTH, TETRINOS_HEIGHT));
        float float_x = (float)frame_a[i].x;
        float float_y = (float)frame_a[i].y;
        sTetrinos.setPosition(float_x * FACTOR, float_y * FACTOR);
        sTetrinos.move(28, 31); //offset to fit within frame
        game->window.draw(sTetrinos);
    }

    // Frame
    game->window.draw(sFrame);
    
    // Font
    game->window.draw(text);
}

void PlayState::update(const float dt)
{
    timer += dt;

    // check for complete line
    is_complete();
    
    // Movement
    for (int i = 0; i < 4; ++i)
    {
        frame_b[i] = frame_a[i];
        frame_a[i].x += dx;
    }
    if (!Check())
    {
        for (int i = 0; i < 4; ++i)
        {
            frame_a[i] = frame_b[i];
        }
    }

    // falling mechanism
    if (timer > delay)
    {
        // fall in the +ve y-direction
        for (int i = 0; i < 4; ++i)
        {
            frame_b[i] = frame_a[i];
            frame_a[i].y += 1;
        }
        if (!Check())
        {
            for (int i = 0; i < 4; ++i)
            {
                field[frame_b[i].y][frame_b[i].x] = colournum;
            }
            // randomly chooses the piece type and colour
            colournum = 1 + rand() % 7; //colour number from tiles.png
            n = rand() % 7; // tile pieces
            for (int i = 0; i < 4; i++)
            {
                frame_a[i].x = tetrinos[n][i] % 2;
                frame_a[i].y = tetrinos[n][i] / 2;
            }
        }
        timer = 0; // Reset timer once condition is true
    }

    // rotate
    if (rotate)
    {
        position ctr = frame_a[1]; // center of rotation
        for (int i = 0; i < 4; ++i)
        {
            int x = frame_a[i].y - ctr.y;
            int y = frame_a[i].x - ctr.x;
            frame_a[i].x = ctr.x - x;
            frame_a[i].y = ctr.y + y;
        }
        if (!Check())
        {
            for (int i = 0; i < 4; ++i)
            {
                frame_a[i] = frame_b[i];
            }
        }
        rotate = 0; // Reset rotate once condition is true
    }

    // Check if Game is over
    if (GameOver() == GAME_STATE::GAME_OVER)
    {   
        game_over_state();
    }

    // reset variables
    dx = 0; delay = DELAY;
}

void PlayState::handleInput()
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

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                game_over_state();
                std::cout << "Pressed ESC." << std::endl;
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                rotate = true;
                play_sound();
                std::cout << "Pressed up." << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                dx = -1;
                play_sound();
                std::cout << "Pressed left." << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                dx = 1;
                play_sound();
                std::cout << "Pressed right." << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                delay = SPEED_UP;
                play_sound();
                std::cout << "Pressed down." << std::endl;
            }
            break;
        default:
            break; // prevent unknown cases
        }
    }
}

void PlayState::PauseGame()
{

}

bool PlayState::Check()
{
    for (int i = 0; i < 4; ++i)
    {
        // check if pieces are within field of n x m
        if ((frame_a[i].x < 0) || (frame_a[i].x >= N) || (frame_a[i].y >= M))
        {
            return 0;
        }
        // collision detection
        else if (field[frame_a[i].y][frame_a[i].x])
        {
            return 0;
        }
    }
    return 1;
}

GAME_STATE PlayState::GameOver()
{
    for (int i = 0; i < N; ++i)
    {
        if (field[1][i]) // check if the top most col is occupied, if occupied == game over
        {
            return GAME_STATE::GAME_OVER;
            break; // o(n)
        }
    }
    return GAME_STATE::GAME_IN_PROGRESS;
}

// Understand this pls
void PlayState::is_complete()
{
    int k = M - 1; // to prevent going out of playing field
    for (int i = k; i > 0; --i)
    {
        int count = 0; // Checks horizontally if all the tiles are filled up
        for (int j = 0; j < N; ++j)
        {
            // if field is occupied, count++
            if (field[i][j])
            {
                count++;
            }
            field[k][j] = field[i][j]; // line above = new current line = everything above completed line shifts down
        }
        if (count < N)
        {
            k--; // k needs to be updated to correspond to updating i
        }
        if (count == N)
        {
            cmplt_sound.play();
        }
    }
}

void PlayState::game_over_state()
{
    gm_over_sound.play();
    game->pushState(new GameOverState(game));
}

void PlayState::play_sound()
{
    press_sound.play();
}
