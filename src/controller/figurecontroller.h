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
    Commands lastCommand{NO_COMMAND};

    void swapCurrentFigure();

public:
    FigureController();
    bool turnStart(Field& field);
    void turnEnd(Field& field);
    void doCommand(Field& field, Commands command);
    bool isSwapNeeded(Field& field);
    FigureBase getCurrentFigure();
    std::array<FigureBase, 3> getNextFigures();
};

#endif //FIGURE_CONTROLLER_H