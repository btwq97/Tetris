#include "PlayState.h"

int field[M][N] = { 0 };

// swap between 2 frames to give illusion of moving
struct position
{
    int x, y;
} frame_a[4], frame_b[4];

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

void PlayState::draw(const float dt)
{
    /*
        Figure out why Tetrinos does not want to show up
    */
    // Falling Tetrinos
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; j++)
        {
            if (field[i][j] == 0)
            {
                continue;
            }
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

    // Background
    game->window.draw(sBackground);
    // Frame
    game->window.draw(sFrame);
}

void PlayState::update(const float dt)
{
    this->timer += dt;

    // Movement
    for (int i = 0; i < 4; ++i)
    {
        frame_b[i] = frame_a[i];
        frame_a[i].x += dx;
    }
    if (!this->Check())
    {
        for (int i = 0; i < 4; ++i)
        {
            frame_a[i] = frame_b[i];
        }
    }

    // falling mechanism
    if (this->timer > this->delay)
    {
        // fall in the +ve y-direction
        for (int i = 0; i < 4; ++i)
        {
            frame_b[i] = frame_a[i];
            frame_a[i].y += 1;
        }
        if (! this->Check())
        {
            for (int i = 0; i < 4; ++i)
            {
                field[frame_b[i].y][frame_b[i].x] = colournum;
            }
            // randomly chooses the piece type and colour
            this->colournum = 1 + rand() % 7; //colour number from tiles.png
            this->n = rand() % 7; // tile pieces
            for (int i = 0; i < 4; i++)
            {
                frame_a[i].x = tetrinos[n][i] % 2;
                frame_a[i].y = tetrinos[n][i] / 2;
            }
        } 
    }

    // rotate
    if (this->rotate)
    {
        position ctr = frame_a[1]; // center of rotation
        for (int i = 0; i < 4; ++i)
        {
            int x = frame_a[i].y - ctr.y;
            int y = frame_a[i].x - ctr.x;
            frame_a[i].x = ctr.x - x;
            frame_a[i].y = ctr.y + y;
        }
        if (! this->Check())
        {
            for (int i = 0; i < 4; ++i)
            {
                frame_a[i] = frame_b[i];
            }
        }
    }

    // check for complete line
    is_complete();

    // Check if Game is over
    if (this->GameOver() == GAME_STATE::GAME_OVER)
    {

    }

    // reset variables
    this->dx = RELEASE_POINT; this->rotate = 0; this->delay = DELAY;
}

void PlayState::handleInput()
{
    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                PauseGame();
            if (event.key.code == sf::Keyboard::Up)
            {
                this->rotate = true;
                std::cout << "Pressed up." << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                this->dx = -1;
                std::cout << "Pressed left." << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                this->dx = 1;
                std::cout << "Pressed right." << std::endl;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                this->delay = SPEED_UP;
                std::cout << "Pressed down." << std::endl;
            }
            break;
        default:
            break; // prevent unknown cases
        }
    }
}

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
    sTetrinos.setScale(targetSize.x / sTetrinos.getLocalBounds().width, targetSize.y / sTetrinos.getLocalBounds().height);
    this->game = game;
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

void PlayState::is_complete()
{
    int k = M - 1; // to prevent going out of playing field
    for (int i = k; i > 0; --i)
    {
        int count = 0;
        for (int j = 0; j < n; ++j)
        {
            // if field is occupied, count++
            if (field[i][j])
            {
                count++;
            }
            //std::cout << "i: " << i << " j: " << j << " k: " << k << " count: " << count << std::endl;
            field[k][j] = field[i][j]; // line above = new current line = everything above completed line shifts down
        }
        if (count < n)
        {
            k--; // k needs to be updated to correspond to updating i
        }
    }
}