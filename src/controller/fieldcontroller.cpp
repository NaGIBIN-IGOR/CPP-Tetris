#include "fieldcontroller.h"

#include "../model/field.h"
#include <algorithm>
#include "../model/figureenum.h"

FieldController::FieldController() : field(std::make_shared<Field>())
{
}

Field &FieldController::getField()
{
    return *field;
}

unsigned FieldController::removeFullRows()
{
    unsigned blocksRemoved{};
    auto& _field{field->getField()};
    for (auto it{_field.begin()}; it != _field.end(); ++it)
    {
        auto& row{*it};
        if (std::all_of(row.begin(), row.end(),
                        [](ModelConfig::ModelType v)
                        {
                            if (v != static_cast<ModelConfig::ModelType>(EMPTY))
                            {
                                return true;
                            }
                            return false;
                        }))
        {
            std::copy(_field.begin(), it, _field.begin()+1);
            blocksRemoved += row.size();
        }
    }
    return blocksRemoved;
}
