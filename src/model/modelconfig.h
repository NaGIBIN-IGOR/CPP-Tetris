#ifndef MODEL_CONFIG_H
#define MODEL_CONFIG_H

#include <array>
#include <iostream>

namespace ModelConfig
{
    using CoordinateType = int16_t; // должен быть знаковым
    constexpr CoordinateType FIELD_WIDE{10}, FIELD_HEIGHT{20};
    using ModelType = uint8_t;
    using FieldRow = std::array<ModelType, FIELD_WIDE>;
    using Field = std::array<FieldRow, FIELD_HEIGHT>;

};
struct Point
{
    ModelConfig::CoordinateType x, y;
    Point(ModelConfig::CoordinateType x_, ModelConfig::CoordinateType y_) : x(x_), y(y_) {}

    bool operator==(const Point& other) const{
        return x == other.x && y == other.y;
    }
};

const Point DummyPoint{-1, -1};

namespace ModelConfig
{
    using Figure = std::array<Point, 4>;
}

namespace std
{
    template <>
    class hash<Point>
    {
    public:
        std::uint64_t operator()(const Point &pt) const
        {
            return static_cast<std::uint64_t>(((pt.x + pt.y) * (pt.x + pt.y + 1) / 2) + pt.y);
        }
    };
}
#endif // MODEL_CONFIG_H