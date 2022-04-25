#include <iostream>
#include <string>
#include <vector>
#include <SFML\Graphics\Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSSFMLView.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Grafika w C++/SFML");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    MinesweeperBoard board(10, 10, EASY);
    MSSFMLView view(board); 

    int pom = 0;
    while (window.isOpen())
    {
        if (pom % 100 == 0)
        {
            board.debug_display();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            view.mouse(window, event);
        }

        window.clear();
        view.draw(window);
        view.Game();
        window.display();
        pom++;
    }
   


    return 0;
}