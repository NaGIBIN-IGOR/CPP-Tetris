#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include <ostream>
#include <vector>
#include "view.h"

#include <memory>

class ConsoleView : public View
{
private:
    std::vector<std::ostream*> outs;
public:
    ConsoleView();
    void renderGame(const GameViewInfo& gameViewInfo) override;
};



#endif //CONSOLE_VIEW_H