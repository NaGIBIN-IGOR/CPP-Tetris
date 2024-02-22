#include "sfmlview.h"

#include "../model/figureenum.h"
#include <unordered_map>
#include <SFML/Graphics/Text.hpp>

SFMLView::SFMLView(sf::RenderWindow &w) : window(w)
{
    colors.insert({static_cast<ModelConfig::ModelType>(EMPTY), {sf::Color(21, 21, 21, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(I_FIGURE), {sf::Color(0, 193, 216, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(L_FIGURE), {sf::Color(229, 157, 0, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(J_FIGURE), {sf::Color(0, 112, 211, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(O_FIGURE), {sf::Color(228, 210, 0, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(T_FIGURE), {sf::Color(184, 0, 224, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(S_FIGURE), {sf::Color(0, 227, 64, 255)}});
    colors.insert({static_cast<ModelConfig::ModelType>(Z_FIGURE), {sf::Color(215, 0, 0, 255)}});
    scoreFont.loadFromFile(dataFolder + "/fonts/SuperMario256.ttf");
}

void SFMLView::colorizeBlock(sf::RectangleShape &block,
                 ModelConfig::ModelType modelBlock)
{
    static const auto OutlineColor{sf::Color(25, 25, 25, 255)};
    block.setOutlineColor(OutlineColor);
    block.setOutlineThickness(outlineThickness);
    block.setFillColor(colors[modelBlock]);
}

void SFMLView::fillMapByField(
    std::unordered_map<Point, sf::RectangleShape> &map,
    const GameViewInfo &gameViewInfo)
{
    const auto rowField = gameViewInfo.field.getField();
    for (ModelConfig::CoordinateType i = 0; i < gameViewInfo.field.height; ++i)
    {
        for (ModelConfig::CoordinateType j = 0; j < gameViewInfo.field.wide; ++j)
        {
            sf::RectangleShape block(sf::Vector2f(actualBlockSize, actualBlockSize));
            block.setPosition(sf::Vector2f(j * blockSize, i * blockSize));
            colorizeBlock(block, rowField[i][j]);
            map.insert({Point{j, i}, block});
        }
    }
}

void SFMLView::drawScore(const GameViewInfo &gameViewInfo, ModelConfig::CoordinateType yCoordinate)
{
    sf::Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setString(std::to_string(gameViewInfo.score));
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOrigin(scoreText.getLocalBounds().width / 2.f, scoreText.getLocalBounds().height / 2.f);
    scoreText.setPosition((ModelConfig::FIELD_WIDE + 4) * blockSize, yCoordinate * blockSize);
    window.draw(scoreText);
}

void SFMLView::drawFigure(std::unordered_map<Point, sf::RectangleShape> &map, const GameViewInfo &gameViewInfo)
{
    const auto rowFigure = gameViewInfo.currentFigure.getFigure();
    const auto coords{gameViewInfo.currentFigure.getCoordinates()};
    for (const auto& elem: rowFigure){
        auto& block = map[Point{
            static_cast<ModelConfig::CoordinateType>(coords.x + elem.x),
            static_cast<ModelConfig::CoordinateType>(coords.y + elem.y)}];
        colorizeBlock(block, gameViewInfo.currentFigure.getFiller());
    }
}

void SFMLView::drawNextFigures(const GameViewInfo &gameViewInfo,
                    ModelConfig::CoordinateType yCoordinate)
{
    auto &nextFigures{gameViewInfo.nextFigures};

    unsigned currentY{3};
    for (auto &fig : nextFigures)
    {
        for (auto &p : fig.getFigure())
        {
            sf::RectangleShape block(sf::Vector2f(actualBlockSize, actualBlockSize));
            block.setPosition(
                (ModelConfig::FIELD_WIDE + 1 + p.x) * blockSize,
                (currentY + p.y) * blockSize);
            colorizeBlock(block, fig.getFiller());
            window.draw(block);
        }
        currentY += fig.getFigure().size();
    }
}

void SFMLView::drawShadow(std::unordered_map<Point, sf::RectangleShape> &map, const GameViewInfo &gameViewInfo)
{   
    const auto rowFigure = gameViewInfo.currentFigure.getFigure();
    const auto coords{gameViewInfo.currentFigure.getCoordinates()};
    const auto shadowOffset{gameViewInfo.shadowCoordinate};
    for (const auto& elem: rowFigure){
        auto& block = map[Point{
            static_cast<ModelConfig::CoordinateType>(coords.x + elem.x),
            static_cast<ModelConfig::CoordinateType>(shadowOffset + elem.y)}];
        block.setOutlineColor(colors[static_cast<ModelConfig::ModelType>(gameViewInfo.currentFigure.getFiller())]);
        block.setOutlineThickness(outlineThickness);

    }
}

void SFMLView::colorizeEmptyBlocks(
    std::unordered_map<Point, sf::RectangleShape> &map,
    const GameViewInfo &gameViewInfo)
{
    const auto rowField = gameViewInfo.field.getField();
    for(auto& elem: map) {
        if(elem.second.getFillColor() == sf::Color::White) {
            colorizeBlock(elem.second, rowField[elem.first.x][elem.first.y]);   
        }
    }
}

void SFMLView::renderGame(const GameViewInfo &gameViewInfo)
{
    window.clear();

    auto &figure{gameViewInfo.currentFigure.getFigure()};
    auto currentPosition{gameViewInfo.currentFigure.getCoordinates()};
    auto filler{gameViewInfo.currentFigure.getFiller()};

    std::unordered_map<
        Point,sf::RectangleShape>
        shapes{gameViewInfo.field.height * gameViewInfo.field.wide};
    fillMapByField(shapes, gameViewInfo);
    drawShadow(shapes, gameViewInfo);
    drawFigure(shapes, gameViewInfo);
    drawScore(gameViewInfo, 1);
    drawNextFigures(gameViewInfo, 6);
    for(const auto& elem: shapes) {
        window.draw(elem.second);
    }
    window.display();   
}
