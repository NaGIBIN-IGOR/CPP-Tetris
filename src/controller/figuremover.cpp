#include "figuremover.h"
#include "../model/field.h"
#include "../model/figures.h"

#include <algorithm>
#include <array>

bool FigureMover::isValidCoordinate(
    ModelConfig::CoordinateType maxX,
    ModelConfig::CoordinateType maxY,
    ModelConfig::CoordinateType baseX,
    ModelConfig::CoordinateType baseY,
    ModelConfig::CoordinateType offsetX,
    ModelConfig::CoordinateType offsetY)
{
    if (
        baseX < 0 ||
        baseY < 0 ||
        baseY + offsetY < 0 ||
        baseY + offsetY >= maxY ||
        baseX + offsetX >= maxX)
        return false;
    return true;
}

bool FigureMover::canFigureBeSet(
    Field &field_,
    FigureBase &figure_,
    ModelConfig::CoordinateType newx,
    ModelConfig::CoordinateType newy)
{
    auto &field{field_.getField()};
    auto &figure{figure_.getFigure()};
    for (const auto &figPoint : figure)
    {
        if (!isValidCoordinate(
                field_.wide,
                field_.height,
                newx,
                newy,
                figPoint.x,
                figPoint.y) ||
            field[newy + figPoint.y][newx + figPoint.x] != EMPTY)
        {
            return false;
        }
    }
    return true;
}

bool FigureMover::canFigureBeSet(Field &field_, FigureBase &figure_)
{
    auto &field{field_.getField()};
    auto &figure{figure_.getFigure()};
    auto currentPosition{figure_.getCoordinates()};
    for (const auto &figPoint : figure)
    {
        if (!isValidCoordinate(
                field_.wide,
                field_.height,
                currentPosition.x,
                currentPosition.y,
                figPoint.x,
                figPoint.y) ||
            field[currentPosition.y + figPoint.y][currentPosition.x + figPoint.x] != EMPTY)
        {
            return false;
        }
    }
    return true;
}

void FigureMover::deleteFigureFromField(Field &field_, const FigureBase &figure_)
{
    auto &field{field_.getField()};
    const auto &figure{figure_.getFigure()};
    auto currentPosition{figure_.getCoordinates()};
    for (const auto &figPoint : figure)
    {
        field[currentPosition.y + figPoint.y][currentPosition.x + figPoint.x] = EMPTY;
    }
}

bool FigureMover::setFigureOnField(Field &field_, FigureBase &figure_)
{
    auto &field{field_.getField()};
    auto &figure{figure_.getFigure()};
    auto currentPosition{figure_.getCoordinates()};
    if (canFigureBeSet(field_, figure_))
    {
        for (const auto &figPoint : figure)
        {
            field[currentPosition.y + figPoint.y][currentPosition.x + figPoint.x] = figure_.getFiller();
        }
        return true;
    }
    return false;
}

void FigureMover::moveFigureRight(Field &field_, FigureBase &figure_)
{
    auto currentPosition{figure_.getCoordinates()};
    if (canFigureBeSet(field_, figure_, currentPosition.x + 1, currentPosition.y))
    {
        figure_.setCoordinates(currentPosition.y, currentPosition.x + 1);
    }
}

void FigureMover::moveFigureLeft(Field &field_, FigureBase &figure_)
{
    auto currentPosition{figure_.getCoordinates()};
    if (canFigureBeSet(field_, figure_, currentPosition.x - 1, currentPosition.y))
    {
        figure_.setCoordinates(currentPosition.y, currentPosition.x - 1);
    }
}

void FigureMover::moveFigureDown(Field &field_, FigureBase &figure_)
{
    auto currentPosition{figure_.getCoordinates()};
    if (canFigureBeSet(field_, figure_, currentPosition.x, currentPosition.y + 1))
    {
        figure_.setCoordinates(currentPosition.y + 1, currentPosition.x);
    }
}

void FigureMover::dropFigure(Field &field_, FigureBase &figure_)
{
    auto newY{getDropYCoordinate(field_, figure_)};
    figure_.setCoordinates(newY, figure_.getCoordinates().x);
}

void FigureMover::rotateFigureLeft(Field &field_, FigureBase &figure_)
{
    figure_.rotateLeft();
    if (canFigureBeSet(field_, figure_))
        return;
    auto coordsFig{figure_.getCoordinates()};

    if (coordsFig.y <= 0 && canFigureBeSet(field_, figure_, coordsFig.x, 1))
    {
        figure_.setCoordinates(1, coordsFig.x);
        return;
    }
    else if (canFigureBeSet(field_, figure_, coordsFig.x - 1, coordsFig.y))
    {
        figure_.setCoordinates(coordsFig.y, coordsFig.x - 1);
        return;
    }
    else if (canFigureBeSet(field_, figure_, coordsFig.x + 1, coordsFig.y))
    {
        figure_.setCoordinates(coordsFig.y, coordsFig.x + 1);
        return;
    }
    figure_.rotateRight();
}

void FigureMover::rotateFigureRight(Field &field_, FigureBase &figure_)
{
    figure_.rotateRight();
    if (canFigureBeSet(field_, figure_))
        return;
    auto coordsFig{figure_.getCoordinates()};

    if (coordsFig.y <= 0 && canFigureBeSet(field_, figure_, coordsFig.x, 1))
    {
        figure_.setCoordinates(1, coordsFig.x);
        return;
    }
    else if (canFigureBeSet(field_, figure_, coordsFig.x - 1, coordsFig.y))
    {
        figure_.setCoordinates(coordsFig.y, coordsFig.x - 1);
        return;
    }
    else if (canFigureBeSet(field_, figure_, coordsFig.x + 1, coordsFig.y))
    {
        figure_.setCoordinates(coordsFig.y, coordsFig.x + 1);
        return;
    }
    figure_.rotateLeft();
}

ModelConfig::CoordinateType FigureMover::getDropYCoordinate(Field &field_, FigureBase &figure_)
{
    auto currentPosition{figure_.getCoordinates()};
    ModelConfig::CoordinateType minY{};
    ModelConfig::CoordinateType maxY{ModelConfig::FIELD_HEIGHT - 1};
    while (minY <= maxY)
    {
        ModelConfig::CoordinateType midY{(minY + maxY) / 2};

        if (canFigureBeSet(field_, figure_, currentPosition.x, midY))
        {
            minY = midY + 1;
        }
        else
        {
            maxY = midY - 1;
        }
    }
    return maxY;
}
