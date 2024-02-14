#include "game.h"

#include "inputcommands.h"
#include "../view/sfmlview.h"
#include "../view/consoleview.h"

#include <thread>
#include <SFML/Window/Event.hpp>
void Game::_start()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        if (!gameController.turnStart())
        {
            break;
        }
        allRender();
        const auto start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start) <= waitDuration)
        {
            auto com{InputCommands::getCommand()};
            if (com == NO_COMMAND)
            {
                continue;
            }
            else if(com == DROP){
                gameController.doCommand(com);
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                break;
            }
            else{
                gameController.doCommand(com);
            }
            allRender();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        auto blocksRemoved = gameController.turnEnd();
        allRender();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::allRender()
{
    GameViewInfo info{
        .field = gameController.getField(),
        .nextFigures = gameController.getNextFigures(),
        .currentFigure = gameController.getCurrentFigure(),
        .score = 0};
    for (auto &view : views)
    {
        view->renderGame(info);
    }
}

void Game::scoreIncrease(unsigned blocksRemoved)
{
    score += blocksRemoved * 5;
}

Game::Game() : window(sf::VideoMode(300, 600), "Tetris")
{
    views.push_back(std::make_unique<SFMLView>(window));
    // views.push_back(std::make_unique<ConsoleView>());
}

void Game::start()
{
    _start();
}
