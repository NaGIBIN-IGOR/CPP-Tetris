#ifndef FIELD_CONTROLLER_H
#define FIELD_CONTROLLER_H

#include <memory>

class Field;

class FieldController
{
private:
    std::shared_ptr<Field> field;
public:
    FieldController();
    Field& getField();
    unsigned removeFullRows(); 
};


#endif //FIELD_CONTROLLER_H