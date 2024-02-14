#ifndef VIEW_H
#define VIEW_H

#include "gameviewinfo.h"

class View
{
public:
    virtual void renderGame(const GameViewInfo& gameViewInfo)=0;
};


#endif //VIEW_H