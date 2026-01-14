#include <gui/speed_screen/SpeedView.hpp>
#include <gui/speed_screen/SpeedPresenter.hpp>

SpeedPresenter::SpeedPresenter(SpeedView& v)
    : view(v)
{

}

void SpeedPresenter::activate()
{

}

void SpeedPresenter::deactivate()
{

}

void SpeedPresenter::SpeedN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen)
{
	uint32_t u32Data;
    switch (type)
    {
        case fdcan_n2k_speed:
            view.updateSpeed(value);
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
