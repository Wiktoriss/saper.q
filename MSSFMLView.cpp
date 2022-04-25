#include <iostream>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "MSSFMLView.h"
#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"
MSSFMLView::MSSFMLView(MinesweeperBoard& b) : board(b)
{
    kwadratSize = 55;
}

using namespace std;

void MSSFMLView::draw(sf::RenderWindow& win)
{
    sf::Color color1(255, 204, 221);
    sf::Color color2(100, 200, 150);
    sf::RectangleShape r;
    r.setSize(sf::Vector2f(10, 10));
    r.setFillColor(color1);
    r.setPosition(100, 100);
    //win.draw(r);

    sf::RectangleShape kwadrat;
    sf::Text tekst;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    tekst.setFont(font);
    tekst.setCharacterSize(40);
    tekst.setStyle(sf::Text::Regular);
    tekst.setFillColor(sf::Color::Black);
    sf::Vector2f size(50, 50);
    kwadrat.setSize(size);
    kwadrat.setFillColor(color1);
    int pozycjay = 0, pozycjax;


    for (int pozy = 0; pozy < board.getBoardHeight(); pozy++)
    {
        pozycjax = 0; 
        for (int pozx = 0; pozx < board.getBoardWidth(); pozx++)
        {
            pozycjax = kwadratSize*pozx;
            pozycjay = kwadratSize * pozy;

            if (board.isRevealed(pozy, pozx) == false && board.hasFlag(pozy, pozx) == false)
            {
                kwadrat.setFillColor(color1);
                kwadrat.setPosition(pozycjax, pozycjay);
                win.draw(kwadrat);

            }
            if (board.hasFlag(pozy, pozx) == true)
            {
                kwadrat.setFillColor(color1);
                kwadrat.setPosition(pozycjax, pozycjay);
                win.draw(kwadrat);
                tekst.setPosition(pozycjax, pozycjay);
                tekst.setString("F");
                win.draw(tekst);
            }
            if (board.isRevealed(pozy, pozx) == true && board.hasFlag(pozy, pozx) == false && board.countMines(pozy, pozx) == 0)
            {
                kwadrat.setFillColor(color2);
                kwadrat.setPosition(pozycjax, pozycjay);
                win.draw(kwadrat);
            }

            if (board.isRevealed(pozy, pozx) == true && board.hasFlag(pozy, pozx) == false)
            {
                kwadrat.setFillColor(color2);
                kwadrat.setPosition(pozycjax, pozycjay);
                tekst.setPosition(pozycjax, pozycjay);
                win.draw(kwadrat);
                switch (board.countMines(pozy, pozx))
                {
                case 1:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("1");
                    win.draw(tekst);
                    break;
                case 2:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("2");
                    win.draw(tekst);
                    break;
                case 3:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("3");
                    win.draw(tekst);
                    break;
                case 4:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("4");
                    win.draw(tekst);
                    break;
                case 5:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("5");
                    win.draw(tekst);
                    break;
                case 6:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("6");
                    win.draw(tekst);
                    break;
                case 7:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("7");
                    win.draw(tekst);
                    break;
                case 8:
                    tekst.setFillColor(sf::Color::Black);
                    tekst.setString("8");
                    win.draw(tekst);
                    break;

                }
                if (board.isRevealed(pozy, pozx) == 1 && board.hasFlag(pozy, pozx) == 0 && board.hasMine(pozy, pozx) == true)
                {
                    tekst.setFillColor(color2);
                    kwadrat.setFillColor(color1);
                    kwadrat.setPosition(pozycjax, pozycjay);
                    tekst.setPosition(pozycjax + 10, pozycjay - 8);
                    win.draw(kwadrat);
                    tekst.setString("X");
                    win.draw(tekst);
                }
                
            }


        }
        
    }
}

void MSSFMLView::mouse(sf::RenderWindow& win, const sf::Event& event)
{

    int x, y, posx = 0, posy = 0;
    if (event.type == sf::Event::MouseButtonReleased)
    {
        x = event.mouseButton.x;
        y = event.mouseButton.y;

        posx = x / kwadratSize;
        posy = y / kwadratSize;
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            board.revealField(posy, posx);
        }
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            board.toggleFlag(posy, posx);
        }
    }
}

void MSSFMLView::Game()
{
    
    if (board.getGameState() == FINISHED_LOSS)
    {
        board.AllField();
        cout << "PRZEGRANA" << endl;
    }
}