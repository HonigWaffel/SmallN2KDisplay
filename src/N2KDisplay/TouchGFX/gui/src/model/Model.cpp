#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "fdcan.h"

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
    if (!modelListener)
    {
        return; // verhindert Crash!
    }

    for (fdcan_enn2kDATA_t i = (fdcan_enn2kDATA_t)0;
         i != fdcan_n2k_quan;
         i = static_cast<fdcan_enn2kDATA_t>(i + 1))
    {
        if(fdcan_stN2KData[i].boNewData)
        {
            fdcan_stN2KData[i].boNewData = 0;

            float fNewData = fdcan_stN2KData[i].fData;

            modelListener->newN2kValue(i, fNewData, fdcan_stSCREEN_SEL_RAM.u32SelScreen);
            modelListener->SpeedN2kValue(i, fNewData, fdcan_stSCREEN_SEL_RAM.u32SelScreen);
            modelListener->DepthN2kValue(i, fNewData, fdcan_stSCREEN_SEL_RAM.u32SelScreen);
        }
    }
    modelListener->SelScreen(enSelArrow, boMenuActive);
}
