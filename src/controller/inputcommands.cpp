#include "inputcommands.h"

#include "figurecommands.h"

#include <SFML/Window.hpp>

Commands InputCommands::getCommand()
{
    using namespace sf;
    if(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)){
        return LEFT;
    }
    if(Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)){
        return RIGHT;
    }
    if(Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)){
        return DOWN;
    }
    if(Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Enter)){
        return DROP;
    }
    if(Keyboard::isKeyPressed(Keyboard::Z) || Keyboard::isKeyPressed(Keyboard::K)){
        return ROTATE_LEFT;
    }
    if(Keyboard::isKeyPressed(Keyboard::X) || Keyboard::isKeyPressed(Keyboard::L)){
        return ROTATE_RIGHT;
    }
    return NO_COMMAND;
}
