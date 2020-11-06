# Tetris
 Final Tetris with game states. This is a work in progress.

Tested with Visual Studio 2019

1) Download CMake here: https://cmake.org/download/
2) Download SFML here: https://www.sfml-dev.org/download/sfml/2.5.1/
3) Make and build all dependencies libraries.
4) Add the following dependencies in your project:
```
===== ===== ===== ===== ===== DEBUG ===== ===== ===== ===== ======
Additional include directories: [SFML parent directory]\SFML-2.5.1\include; 
Preprocessor: SFML_STATIC; 
Additional library directories: [SFML parent directory]\SFML-2.5.1\lib\Debug;[SFML parent directory]\SFML-2.5.1\extlibs\libs-msvc-universal\x64; 
Additional dependencies: opengl32.lib;openal32.lib;freetype.lib;winmm.lib;gdi32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;ws2_32.lib;sfml-graphics-s-d.lib;sfml-window-s-d.lib;sfml-system-s-d.lib;sfml-audio-s-d.lib;sfml-network-s-d.lib; 
===== ===== ===== ===== ===== RELEASE ===== ===== ===== ===== ====== 
Additional include directories: [SFML parent directory]\SFML-2.5.1\include; 
Preprocessor: SFML_STATIC;
Additional library directories: [SFML parent directory]\SFML-2.5.1\lib\Release;[SFML parent directory]\SFML-2.5.1\extlibs\libs-msvc-universal\x64; 
Additional dependencies: opengl32.lib;openal32.lib;freetype.lib;winmm.lib;gdi32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;ws2_32.lib;sfml-graphics-s.lib;sfml-window-s.lib;sfml-system-s.lib;sfml-audio-s.lib;sfml-network-s.lib;
```
5) Test with the following code. If build success, it'll produce a green circle.
```
===== ===== ===== ===== ===== TEST CODE ===== ===== ===== ===== ====== 
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
6) Run code in Debug mode and see the Tetris game run.
