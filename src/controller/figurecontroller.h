#ifndef FIGURE_CONTROLLER_H
#define FIGURE_CONTROLLER_H

#include "figuregenerator.h"
#include "figuremover.h"
#include "./figurecommands.h"

#include <tuple>

class FigureController
{
private:
    FigureGenerator figureGenerator{};
    FigureBase currentFigure;
    void swapCurrentFigure();
public:
    FigureController();
    bool turnStart(Field& field);
    void turnEnd(Field& field);
    void doCommand(Field& field, Commands command);
    bool isSwapNeeded(Field& field);
    FigureBase getCurrentFigure();
    std::tuple<FigureBase, FigureBase, FigureBase> getNextFigures();
};

#endif //FIGURE_CONTROLLER_H