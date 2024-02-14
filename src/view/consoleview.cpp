#include "consoleview.h"

#include "../model/figureenum.h"

#include <sstream>

ConsoleView::ConsoleView()
{
    outs.push_back(&std::cout);
}

void ConsoleView::renderGame(const GameViewInfo &gameViewInfo)
{
    const auto &field = gameViewInfo.field;
    const auto rowField = field.getField();

    std::stringstream out{};
    out << "\x1B[2J\x1B[H" << "  " << std::string(field.wide, '@') << '\n' << std::string(field.wide, '_') << '\n';

    for (auto i = 0; i < field.height; ++i)
    {
        out << '|';
        for (auto j = 0; j < field.wide; ++j)
        {
            switch (static_cast<FigureEnum>(rowField[i][j]))
            {
            case EMPTY:
                out << ' ';
                break;

            case I_FIGURE:
                out << '#';
                break;

            case L_FIGURE:
                out << '#';
                break;

            case J_FIGURE:
                out << '#';
                break;

            case O_FIGURE:
                out << '#';
                break;

            case T_FIGURE:
                out << '#';
                break;

            case S_FIGURE:
                out << '#';
                break;

            case Z_FIGURE:
                out << '#';
                break;
            default:
                break;
            }

        }
        out << '|' << '\n';
    }
    out << std::string(field.wide, '_')  << '\n' << std::string(field.wide, '@') << '\n';
    for(auto& elem: outs){
        (*elem) << out.str();
    }
}
