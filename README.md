# Tetris
Retro style Tetris game. This is a game in progress.
## About
Runs in Ubuntu VS Code.
## DEPENDENCIES
Tested with Ubuntu 18.04
1. Install.
```
$ sudo apt install libsfml-dev -y
```
2. Run Test Code to see if lib is indeed installed properly.
```
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
```
3. Run code
```
$ make
$ ./bin/tetris
```