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
            if (event.type == sf::Event::Closed)
            {
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
            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type != sf::Event::KeyPressed)
                continue;
            auto com{InputCommands::getCommand(event)};
            if (com == NO_COMMAND)
            {
                continue;
            }
            else if (com == DROP)
            {
                gameController.doCommand(com);
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                break;
            }
            else
            {
                gameController.doCommand(com);
            }
            allRender();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        scoreIncrease(gameController.turnEnd());
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
        .shadowCoordinate = gameController.getShadowCoordinate(),
        .score = this->score};
    for (auto &view : views)
    {
        view->renderGame(info);
    }
}

void Game::scoreIncrease(unsigned blocksRemoved)
{
    score += blocksRemoved * 10 * (blocksRemoved / ModelConfig::FIELD_WIDE);
}
Game::Game() : window(sf::VideoMode(ModelConfig::FIELD_WIDE * SFMLView::blockSize + SFMLView::blockSize + 4 * SFMLView::blockSize,
                                    (ModelConfig::FIELD_HEIGHT)*SFMLView::blockSize),
                      "Tetris")
{
    window.setKeyRepeatEnabled(false);
    views.push_back(std::make_unique<SFMLView>(window));
    // views.push_back(std::make_unique<ConsoleView>());
}

void Game::start()
{
    _start();
}
