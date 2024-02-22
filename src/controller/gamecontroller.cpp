#include "gamecontroller.h"

#include "figurecontroller.h"
#include "fieldcontroller.h"
#include "../model/figures.h"
#include "figurecommands.h"

GameController::GameController(): 
    fieldController(std::make_unique<FieldController>()),
    figureController(std::make_unique<FigureController>())
{
}

bool GameController::turnStart()
{
    return figureController->turnStart(fieldController->getField());
}

unsigned GameController::turnEnd()
{
    unsigned blocksRemoved{};
    if(figureController->isSwapNeeded(fieldController->getField())){
        figureController->turnEnd(fieldController->getField());
        blocksRemoved = fieldController->removeFullRows();
    }
    else{
        figureController->turnEnd(fieldController->getField());
    }
    return blocksRemoved;
}

void GameController::doCommand(Commands command)
{
    figureController->doCommand(fieldController->getField(), command);
}

Field &GameController::getField()
{
    return fieldController->getField();
}

FigureBase GameController::getCurrentFigure()
{
    return figureController->getCurrentFigure();
}

std::array<FigureBase, 3> GameController::getNextFigures()
{
    return figureController->getNextFigures();
}

ModelConfig::CoordinateType GameController::getShadowCoordinate()
{
    return figureController->getShadowCoordinate(fieldController->getField());
}
