#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <memory>
#include "figurecommands.h"
#include "figurecontroller.h"
#include "fieldcontroller.h"

class Field; class FigureBase;

class GameController
{
private:
    std::unique_ptr<FigureController> figureController;
    std::unique_ptr<FieldController> fieldController;
public:
    GameController();
    bool turnStart();
    unsigned turnEnd();
    void doCommand(Commands command);
    Field& getField();
    FigureBase getCurrentFigure();
    std::array<FigureBase, 3> getNextFigures();

    ModelConfig::CoordinateType getShadowCoordinate();

};

#endif //GAME_CONTROLLER_H