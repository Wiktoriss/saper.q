#include "SFML/Graphics.hpp"
#include "MinesweeperBoard.h"

class MSSFMLView
{
    int kwadratSize;
    MinesweeperBoard& board;
public:
    explicit MSSFMLView(MinesweeperBoard& b);

    void draw(sf::RenderWindow& win);
    void mouse(sf::RenderWindow& win, const sf::Event& event);
    void Game();
};