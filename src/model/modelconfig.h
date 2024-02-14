#ifndef MODEL_CONFIG_H
#define MODEL_CONFIG_H

#include <array>
#include <iostream>

namespace ModelConfig
{
    constexpr unsigned FIELD_WIDE{10}, FIELD_HEIGHT{20};
    using ModelType = uint8_t;
    using FieldRow = std::array<ModelType,FIELD_WIDE>;
    using Field = std::array<FieldRow, FIELD_HEIGHT>;
    using CoordinateType = int16_t; // должен быть знаковым

};
struct Point
{
    ModelConfig::CoordinateType x,y;
    Point(ModelConfig::CoordinateType x_, ModelConfig::CoordinateType y_): x(x_),  y(y_){}
};

const Point DummyPoint{-1,-1};

namespace ModelConfig{
    using Figure = std::array<Point, 4>;
}


#endif //MODEL_CONFIG_H