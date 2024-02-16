#ifndef SFML_VIEW_H
#define SFML_VIEW_H

#include "view.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class SFMLView: public View
{
private:
    sf::RenderWindow& window;
    void colorBlock(sf::RectangleShape &block, ModelConfig::ModelType modelBlock);

public:
    static const unsigned blockSize{30};
    SFMLView(sf::RenderWindow& w);
    void renderGame(const GameViewInfo& gameViewInfo) override;

};

#endif //SFML_VIEW_H