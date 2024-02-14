#ifndef FIELD_H
#define FIELD_H

#include "modelconfig.h"

class Field{
private:
    ModelConfig::Field _field{};
    
public:
    static const unsigned wide{ModelConfig::FIELD_WIDE}, height{ModelConfig::FIELD_HEIGHT};
    Field()=default;
    ModelConfig::Field& getField(){return _field;}
    const ModelConfig::Field& getField() const {return _field;}
    ModelConfig::ModelType getValueByCoordinate(ModelConfig::CoordinateType y, ModelConfig::CoordinateType x);
    void setValueByCoordinate(ModelConfig::CoordinateType y, ModelConfig::CoordinateType x, ModelConfig::ModelType v);
};

#endif //FIELD_H