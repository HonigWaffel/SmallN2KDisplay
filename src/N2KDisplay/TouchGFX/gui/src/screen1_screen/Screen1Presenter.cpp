#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::newN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen)
{
	uint32_t u32Data;
    switch (type)
    {
        case fdcan_n2k_speed:
            view.updateSpeed(value);
            break;

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
