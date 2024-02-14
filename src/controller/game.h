#ifndef GAME_H
#define GAME_H

#include "gamecontroller.h"
#include "../model/field.h"
#include "../view/view.h"

#include <chrono>
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class SFMLView;

class Game
{
private:
    GameController gameController{};
    std::chrono::milliseconds waitDuration{1000};
    std::vector<std::unique_ptr<View>> views{};
    sf::RenderWindow window;
    unsigned score{};
    
    void _start();
    void allRender();
    void scoreIncrease(unsigned);
public:
    Game();
    void start();
};


#endif //GAME_H