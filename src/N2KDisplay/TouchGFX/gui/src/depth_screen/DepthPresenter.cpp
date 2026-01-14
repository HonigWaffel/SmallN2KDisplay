#include <gui/depth_screen/DepthView.hpp>
#include <gui/depth_screen/DepthPresenter.hpp>

DepthPresenter::DepthPresenter(DepthView& v)
    : view(v)
{

}

void DepthPresenter::activate()
{

}

void DepthPresenter::deactivate()
{

}

void DepthPresenter::DepthN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen)
{
	uint32_t u32Data;
    switch (type)
    {
        case fdcan_n2k_depth:
            view.updateDepth(value);
            break;

        case fdcan_n2k_nmode:
        	u32Data = (uint32_t)value;
        	if (u32Data == 0xFFFFFFFF)
        	{
    			view.setDarkMode(false);
        	}
        	else
        	{
    			view.setDarkMode(true);
        	}
			break;

        default:
            break;
    }
    view.changeScreen((uint8_t)u32Screen);
}
