#ifndef SFML_VIEW_H
#define SFML_VIEW_H

#include "view.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>

class SFMLView : public View
{
private:
    std::unordered_map<ModelConfig::ModelType, sf::Color> colors;
    sf::RenderWindow &window;
    sf::Font scoreFont;
    const std::string dataFolder{DATA_FOLDER_PATH};
    float outlineThickness = 1.0;
    void colorizeBlock(sf::RectangleShape &block, ModelConfig::ModelType modelBlock);
    void fillMapByField(std::unordered_map<
                            Point, sf::RectangleShape> &map,
                        const GameViewInfo &gameViewInfo);

    void drawScore(
        const GameViewInfo &gameViewInfo,
        ModelConfig::CoordinateType yCoordinate);
    void drawFigure(std::unordered_map<
                        Point, sf::RectangleShape> &map,
                    const GameViewInfo &gameViewInfo);
    void drawNextFigures(const GameViewInfo &gameViewInfo,
                         ModelConfig::CoordinateType yCoordinate);
    void drawShadow(std::unordered_map<
                        Point, sf::RectangleShape> &map,
                    const GameViewInfo &gameViewInfo);

    void colorizeEmptyBlocks(std::unordered_map<
                        Point, sf::RectangleShape> &map,
                        const GameViewInfo &gameViewInfo);

public:
    static const unsigned blockSize{30};
    const float actualBlockSize = blockSize - 2 * outlineThickness;
    SFMLView(sf::RenderWindow &w);
    void renderGame(const GameViewInfo &gameViewInfo) override;
};

#endif // SFML_VIEW_H