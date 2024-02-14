#include "field.h"

ModelConfig::ModelType Field::getValueByCoordinate(ModelConfig::CoordinateType y, ModelConfig::CoordinateType x)
{
    if(y < ModelConfig::FIELD_HEIGHT && x < ModelConfig::FIELD_WIDE)
        return _field[y][x];
    return ModelConfig::ModelType();
}

void Field::setValueByCoordinate(ModelConfig::CoordinateType y, ModelConfig::CoordinateType x, ModelConfig::ModelType v)
{
    if(y < ModelConfig::FIELD_HEIGHT && x < ModelConfig::FIELD_WIDE)
        _field[y][x] = v;
}
