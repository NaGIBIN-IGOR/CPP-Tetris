#include "sfmlview.h"

#include "../model/figureenum.h"
#include <unordered_set>

SFMLView::SFMLView(sf::RenderWindow &w) : window(w)
{
}

void SFMLView::colorBlock(sf::RectangleShape &block, ModelConfig::ModelType modelBlock)
{
    static const auto emptyBlockColor{sf::Color(21, 21, 21, 255)};
    static const auto IFigureBlockColor{sf::Color(0, 193, 216, 255)};
    static const auto LFigureBlockColor{sf::Color(229, 157, 0, 255)};
    static const auto JFigureBlockColor{sf::Color(0, 112, 211, 255)};
    static const auto OFigureBlockColor{sf::Color(228, 210, 0, 255)};
    static const auto TFigureBlockColor{sf::Color(184, 0, 224, 255)};
    static const auto SFigureBlockColor{sf::Color(0, 227, 64, 255)};
    static const auto ZFigureBlockColor{sf::Color(215, 0, 0, 255)};
    static const auto OutlineColor{sf::Color(25, 25, 25, 255)};

    block.setOutlineColor(OutlineColor);
    block.setOutlineThickness(0.5);

    switch (static_cast<FigureEnum>(modelBlock))
    {
    case EMPTY:
        block.setFillColor(emptyBlockColor);
        break;

    case I_FIGURE:
        block.setFillColor(IFigureBlockColor);
        break;

    case L_FIGURE:
        block.setFillColor(LFigureBlockColor);
        break;

    case J_FIGURE:
        block.setFillColor(JFigureBlockColor);
        break;

    case O_FIGURE:
        block.setFillColor(OFigureBlockColor);
        break;

    case T_FIGURE:
        block.setFillColor(TFigureBlockColor);
        break;

    case S_FIGURE:
        block.setFillColor(SFigureBlockColor);
        break;

    case Z_FIGURE:
        block.setFillColor(ZFigureBlockColor);
        break;
    default:
        block.setFillColor(sf::Color::White);
        break;
    }
}

void SFMLView::renderGame(const GameViewInfo &gameViewInfo)
{
    const auto &field = gameViewInfo.field;
    const auto rowField = field.getField();
    auto &figure{gameViewInfo.currentFigure.getFigure()};
    auto currentPosition{gameViewInfo.currentFigure.getCoordinates()};
    auto filler{gameViewInfo.currentFigure.getFiller()};

    static auto hash = [](const Point &pt)
    {
        return (size_t)(pt.x * 100 + pt.y);
    };

    static auto equal = [](const Point &pt1, const Point &pt2)
    {
        return ((pt1.x == pt2.x) && (pt1.y == pt2.y));
    };

    std::unordered_set<Point, decltype(hash), decltype(equal)> figureCoords(4, hash, equal);
    for (auto elem : figure)
    {
        figureCoords.emplace(
            elem.x + currentPosition.x,
            elem.y + currentPosition.y);
    }
    window.clear();
    for (ModelConfig::CoordinateType i = 0; i < field.height; ++i)
    {
        for (ModelConfig::CoordinateType j = 0; j < field.wide; ++j)
        {
            sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
            block.setPosition(j * blockSize, i * blockSize);
            if (figureCoords.find(Point{j, i}) == figureCoords.end())
            {
                colorBlock(block, rowField[i][j]);
            }
            else
            {
                colorBlock(block, filler);
            }
            window.draw(block);
        }
    }

    auto &nextFigures{gameViewInfo.nextFigures};

    unsigned currentY{1};
    for (auto &fig : nextFigures)
    {
        for (auto &p : fig.getFigure())
        {
            sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
            block.setPosition(
                (ModelConfig::FIELD_WIDE + 1 + p.x) * blockSize,
                (currentY + p.y)*blockSize);            
            colorBlock(block, fig.getFiller());
            window.draw(block);
        }
        currentY += fig.getFigure().size();
    }

    window.display();
}
