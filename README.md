# Tetris Game
Retro style tetris game. This is a game in progress.

## About
Runs in Windows VS Code.

## DEPENDENCIES
1. Download [MinGW](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download "MinGW").
2. Download [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/ "SFML").
    1. Download the "GCC 7.3.0 MinGW (DW2) - 32-bit" version.
    2. Make sure MINGW is added into environment PATH. See [link](https://code.visualstudio.com/docs/cpp/config-mingw).
3. Test with the following code. If successful, it'll produce a green circle.
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
## Running Tetris
1. Open Terminal in VSC.
2. PS> mingw32-make all (or any other make you installed using MINGW)
3. PS> .\bin\tetris.exe