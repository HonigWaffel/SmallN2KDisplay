#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

#include <cstdio>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Color.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void newN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen) {}
    virtual void SpeedN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen) {}
    virtual void DepthN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen) {}
    virtual void SelScreen(fdcan_enSEL_SCREEN_t enArrow, bool boConf) {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
