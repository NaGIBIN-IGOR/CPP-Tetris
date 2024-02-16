#ifndef FIGURE_GENERATOR_H
#define FIGURE_GENERATOR_H

#include <array>
#include "../model/figures.h"

constexpr unsigned tetraminoNumber{7};

class FigureGenerator
{
private:
    std::array<FigureBase, 2 * tetraminoNumber> _bug{};
    unsigned currentBugIndex{};
    std::array<FigureBase, 3> nextFigures{};
    void shuffle(size_t offset=0);
 public:
    FigureGenerator();
    FigureBase getFigure();
    std::array<FigureBase, 3> getNextFigures();
};

#endif //FIGURE_GENERATOR_H