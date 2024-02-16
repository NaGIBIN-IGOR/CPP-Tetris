#include "figuregenerator.h"
#include <algorithm>
#include <random>

static std::random_device randomDevice{};
static std::mt19937 generator{randomDevice()};

void FigureGenerator::shuffle(size_t offset)
{
    std::shuffle(_bug.begin(), _bug.end() - offset, generator);
}

FigureGenerator::FigureGenerator()
{
    _bug[0] = IFigure();
    _bug[1] = IFigure();
    _bug[2] = LFigure();
    _bug[3] = LFigure();
    _bug[4] = JFigure();
    _bug[5] = JFigure();
    _bug[6] = SFigure();
    _bug[7] = SFigure();
    _bug[8] = ZFigure();
    _bug[9] = ZFigure();
    _bug[10] = TFigure();
    _bug[11] = TFigure();
    _bug[12] = OFigure();
    _bug[13] = OFigure();
    shuffle();
    nextFigures[0] = _bug[currentBugIndex++];
    nextFigures[1] = _bug[currentBugIndex++];
    nextFigures[2] = _bug[currentBugIndex++];
}

FigureBase FigureGenerator::getFigure()
{
    auto ret{nextFigures[0]};
    std::copy(nextFigures.begin() + 1, nextFigures.end(), nextFigures.begin());
    nextFigures[nextFigures.size() - 1] = _bug[currentBugIndex++];
    if (currentBugIndex == _bug.size() - 2)
    {
        currentBugIndex = 0;
        shuffle();
    }
    return ret;
}

std::array<FigureBase, 3> FigureGenerator::getNextFigures()
{
    return nextFigures;
}
