#ifndef FIGURE_MOVER_H
#define FIGURE_MOVER_H

#include "../model/figures.h"
#include "../model/field.h"

class FigureMover
{

private:
    static bool isValidCoordinate(
            ModelConfig::CoordinateType maxX,
            ModelConfig::CoordinateType maxY,
            ModelConfig::CoordinateType baseX,
            ModelConfig::CoordinateType baseY,
            ModelConfig::CoordinateType offsetX,
            ModelConfig::CoordinateType offsetY
        );
public:
    static bool canFigureBeSet(
        Field& field_,
        FigureBase& figure_,
        ModelConfig::CoordinateType newx,
        ModelConfig::CoordinateType newy);
    static bool canFigureBeSet(
        Field& field_,
        FigureBase& figure_);
    static void deleteFigureFromField(Field &field_, const FigureBase &figure_);
    static bool setFigureOnField(Field &field_, FigureBase &figure_);
    static void moveFigureRight(Field &field_, FigureBase &figure_);
    static void moveFigureLeft(Field &field_, FigureBase &figure_);
    static void moveFigureDown(Field &field_, FigureBase &figure_);
    static void dropFigure(Field &field_, FigureBase &figure_);
    static void rotateFigureLeft(Field &field_, FigureBase &figure_);
    static void rotateFigureRight(Field &field_, FigureBase &figure_);
    static ModelConfig::CoordinateType getDropYCoordinate(Field &field_, FigureBase &figure_);
};


#endif //FIGURE_MOVER_H