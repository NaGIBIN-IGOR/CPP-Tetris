#ifndef FIGURES_H
#define FIGURES_H

#include "modelconfig.h"
#include "figureenum.h"

#include <algorithm>

struct FigureBase
{
protected:
    ModelConfig::Figure _figure{DummyPoint, DummyPoint, DummyPoint, DummyPoint};
    Point center{1, 1};
    FigureEnum filler{EMPTY};
    Point coordinates{-1, -1};

    void rotatePoint(
        Point &p,
        ModelConfig::CoordinateType s)
    {
        p.x -= center.x;
        p.y -= center.y;
        auto xnew = -p.y * s;
        auto ynew = p.x * s;
        p.x = xnew + center.x;
        p.y = ynew + center.y;
    }

    void correctFigure()
    { // попровляет фигуру чтобы она соответствовала координатам
        const static auto minX{[](Point &a, Point b)
                               {
                                   if (a.x < b.x)
                                       return true;
                                   return false;
                               }};
        const static auto minY{[](Point &a, Point b)
                               {
                                   if (a.y < b.y)
                                       return true;
                                   return false;
                               }};
        auto minXPoint = std::min_element(_figure.begin(), _figure.end(), minX);
        if (minXPoint->x == 1)
        {
            for (auto &p : _figure)
            {
                p.x -= 1;
            }
        }
        // auto minYPoint = std::min_element(_figure.begin(), _figure.end(), minY);
        // if (minYPoint->y == 1)
        // {
        //     for (auto &p : _figure)
        //     {
        //         p.y -= 1;
        //     }
        // }
    }

public:
    Point getCoordinates() const
    {
        return coordinates;
    }

    void setCoordinates(ModelConfig::CoordinateType y, ModelConfig::CoordinateType x)
    {
        coordinates.x = x;
        coordinates.y = y;
    }

    int getFiller() const
    {
        return filler;
    }

    virtual void rotateLeft()
    {
        static const ModelConfig::CoordinateType s = 1;
        for (auto &p : _figure)
        {
            rotatePoint(p, s);
        }
        correctFigure();
    }

    virtual void rotateRight()
    {
        static const ModelConfig::CoordinateType s = -1;
        for (auto &p : _figure)
        {
            rotatePoint(p, s);
        }
        correctFigure();
    }

    ModelConfig::Figure &getFigure()
    {
        return _figure;
    }

    const ModelConfig::Figure &getFigure() const
    {
        return _figure;
    }
};

class IFigure : public FigureBase
{
public:
    IFigure()
    {
        filler = I_FIGURE;
        _figure[0] = Point(0, 0);
        _figure[1] = Point(1, 0);
        _figure[2] = Point(2, 0);
        _figure[3] = Point(3, 0);
        center.x = 1;
        center.y = 0;
    }
};

class LFigure : public FigureBase
{
public:
    LFigure()
    {
        filler = L_FIGURE;
        _figure[0] = Point(0, 1);
        _figure[1] = Point(1, 1);
        _figure[2] = Point(2, 1);
        _figure[3] = Point(2, 0);
    }
};

class JFigure : public FigureBase
{
public:
    JFigure()
    {
        filler = J_FIGURE;
        _figure[0] = Point(0, 0);
        _figure[1] = Point(0, 1);
        _figure[2] = Point(1, 1);
        _figure[3] = Point(2, 1);
    }
};

class OFigure : public FigureBase
{
public:
    OFigure()
    {
        filler = O_FIGURE;
        _figure[0] = Point(0, 0);
        _figure[1] = Point(0, 1);
        _figure[2] = Point(1, 0);
        _figure[3] = Point(1, 1);
    }
    void rotateLeft() override {}
    void rotateRight() override {}
};

class TFigure : public FigureBase
{
public:
    TFigure()
    {
        filler = T_FIGURE;
        _figure[0] = Point(0, 1);
        _figure[1] = Point(1, 1);
        _figure[2] = Point(2, 1);
        _figure[3] = Point(1, 0);
    }
};

class SFigure : public FigureBase
{
public:
    SFigure()
    {
        filler = S_FIGURE;
        _figure[0] = Point(0, 1);
        _figure[1] = Point(1, 1);
        _figure[2] = Point(1, 0);
        _figure[3] = Point(2, 0);
        center.x = 1;
        center.y = 0;
    }
};

class ZFigure : public FigureBase
{
public:
    ZFigure()
    {
        filler = Z_FIGURE;
        _figure[0] = Point(0, 0);
        _figure[1] = Point(1, 0);
        _figure[2] = Point(1, 1);
        _figure[3] = Point(2, 1);
        center.x = 1;
        center.y = 0;
    }
};

#endif // FIGURES_H