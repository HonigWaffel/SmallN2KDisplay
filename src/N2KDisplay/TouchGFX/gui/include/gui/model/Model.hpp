#ifndef MODEL_HPP
#define MODEL_HPP
#include "fdcan.h"
#include <string.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;
    float fNewData;
};

#endif // MODEL_HPP
