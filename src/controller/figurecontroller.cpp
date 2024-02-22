#include "figurecontroller.h"

constexpr ModelConfig::CoordinateType startX{(ModelConfig::FIELD_WIDE-1)/2}, startY{0};

FigureController::FigureController(){
    swapCurrentFigure();
}

void FigureController::swapCurrentFigure()
{
    currentFigure = figureGenerator.getFigure();
    currentFigure.setCoordinates(startY, startX);
}

bool FigureController::turnStart(Field &field)
{
    if (!FigureMover::canFigureBeSet(field, currentFigure))
    {
        return false;
    }
    return true;
}

void FigureController::turnEnd(Field &field)
{
    auto currentPosition{currentFigure.getCoordinates()};
    if (isSwapNeeded(field))
    {
        FigureMover::setFigureOnField(field, currentFigure);
        swapCurrentFigure();
    }
    else
    {
        currentFigure.setCoordinates(currentPosition.y + 1, currentPosition.x);        
    }
}

void FigureController::doCommand(Field &field, Commands command)
{
    lastCommand = command;
    switch (command)
    {
    case LEFT:
        FigureMover::moveFigureLeft(field, currentFigure);
        break;

    case RIGHT:
        FigureMover::moveFigureRight(field, currentFigure);
        break;

    case DOWN:
        FigureMover::moveFigureDown(field, currentFigure);
        break;

    case DROP:
        FigureMover::dropFigure(field, currentFigure);
        break;

    case ROTATE_LEFT:
        FigureMover::rotateFigureLeft(field, currentFigure);
        break;

    case ROTATE_RIGHT:
        FigureMover::rotateFigureRight(field, currentFigure);
        break;

    default:
        break;
    }
}

std::array<FigureBase, 3> FigureController::getNextFigures()
{
    return figureGenerator.getNextFigures();
}

ModelConfig::CoordinateType FigureController::getShadowCoordinate(Field &field)
{
    return FigureMover::getDropYCoordinate(field, currentFigure);
}


FigureBase FigureController::getCurrentFigure()
{
    return currentFigure;
}

bool FigureController::isSwapNeeded(Field& field)
{
    auto currentPosition{currentFigure.getCoordinates()};
    if(FigureMover::canFigureBeSet(field, currentFigure, currentPosition.x, currentPosition.y + 1)){
        return false;
    }
    return true;
}