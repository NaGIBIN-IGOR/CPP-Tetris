#ifndef INPUT_COMMANDS_H
#define INPUT_COMMANDS_H

#include "figurecommands.h"
#include <SFML/Window/Event.hpp>

class InputCommands
{
public:
    static Commands getCommand(sf::Event& event);
};


#endif //INPUT_COMMANDS_H
