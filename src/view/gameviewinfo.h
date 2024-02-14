#ifndef GAME_VIEW_INFO
#define GAME_VIEW_INFO

#include <tuple>
#include "../model/figures.h"
#include "../model/field.h"

struct GameViewInfo
{
    const Field& field;
    std::tuple<FigureBase, FigureBase, FigureBase> nextFigures;
    FigureBase currentFigure;
    unsigned score;
};


#endif //GAME_VIEW_INFO