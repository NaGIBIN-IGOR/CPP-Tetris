#ifndef FIGURES_H
#define FIGURES_H

#include "modelconfig.h"
#include "figureenum.h"

struct FigureBase
{
protected:
    ModelConfig::Figure _figure{DummyPoint, DummyPoint, DummyPoint, DummyPoint};
    static const ModelConfig::CoordinateType centerX{1};
    static const ModelConfig::CoordinateType centerY{1};
    FigureEnum filler{EMPTY};
    Point coordinates{-1,-1};

    void rotatePoint(
        Point& p,
        ModelConfig::CoordinateType s
        ){
            p.x -= centerX;
            p.y -= centerY;
            auto xnew = - p.y * s;
            auto ynew = p.x * s;
            p.x = xnew + centerX;
            p.y = ynew + centerY;
        }
public:

    Point getCoordinates()const {
        return coordinates;
    }
    
    void setCoordinates(ModelConfig::CoordinateType y, ModelConfig::CoordinateType x){
        coordinates.x = x;
        coordinates.y = y;
    }

    int getFiller() const{
        return filler;
    }

    virtual void rotateLeft(){
        static const ModelConfig::CoordinateType s = 1;
        for(auto& p: _figure){
            rotatePoint(p, s);
        }
    }

    virtual void rotateRight(){
        static const ModelConfig::CoordinateType s = -1;
        for(auto& p: _figure){
            rotatePoint(p, s);
        }
    }

    ModelConfig::Figure& getFigure(){
        return _figure;
    }

    const ModelConfig::Figure& getFigure()const {
        return _figure;
    }
};



class IFigure: public FigureBase
{
public:
    IFigure(){
        filler = I_FIGURE;
        _figure[0] = Point(0,0);
        _figure[1] = Point(0,1);
        _figure[2] = Point(0,2);
        _figure[3] = Point(0,3);
    }
};

class LFigure: public FigureBase
{
public:
    LFigure(){
        filler = L_FIGURE;
        _figure[0] = Point(0,0);
        _figure[1] = Point(0,1);
        _figure[2] = Point(0,2);
        _figure[3] = Point(1,0);
    }
};

class JFigure: public FigureBase
{
public:
    JFigure(){
        filler = J_FIGURE;
        _figure[0] = Point(0,1);
        _figure[1] = Point(0,2);
        _figure[2] = Point(0,3);
        _figure[3] = Point(1,3);
    }
};

class OFigure: public FigureBase
{
public:
    OFigure(){
        filler = O_FIGURE;
        _figure[0] = Point(0,0);
        _figure[1] = Point(0,1);
        _figure[2] = Point(1,0);
        _figure[3] = Point(1,1);

    }
    void rotateLeft() override{}
    void rotateRight() override{}
};

class TFigure: public FigureBase
{
public:
    TFigure(){
        filler = T_FIGURE;
        _figure[0] = Point(0,0);
        _figure[1] = Point(0,1);
        _figure[2] = Point(0,2);
        _figure[3] = Point(1,1);
    }
};

class SFigure: public FigureBase
{
public:
    SFigure(){
        filler = S_FIGURE;
        _figure[0] = Point(1,0);
        _figure[1] = Point(1,1);
        _figure[2] = Point(0,1);
        _figure[3] = Point(0,2);
    }
};

class ZFigure: public FigureBase
{
public:
    ZFigure(){
        filler = Z_FIGURE;
        _figure[0] = Point(0,0);
        _figure[1] = Point(0,1);
        _figure[2] = Point(1,1);
        _figure[3] = Point(1,2);
    }
};

#endif //FIGURES_H