#include <gui/menu_screen/MenuView.hpp>

MenuView::MenuView()
{

}

void MenuView::setupScreen()
{
    MenuViewBase::setupScreen();
}

void MenuView::tearDownScreen()
{
    MenuViewBase::tearDownScreen();
}

void MenuView::SetupScreen(fdcan_enSEL_SCREEN_t enArrow, bool boConf)
{
	switch(enArrow)
	{
	case fdcan_SEL_SCREEN1:
		SpeedDepthArrow.setVisible(true);
		SpeedArrow.setVisible(false);
		DepthArrow.setVisible(false);

		if(boConf)
		{
			boMenuActive = false;
			fdcan_stSCREEN_SEL_RAM.u32SelScreen = (uint32_t)fdcan_SEL_SCREEN1;
			application().gotoScreen1ScreenNoTransition();
			fdcan_vScreenSel_Save();
		}
		break;

	case fdcan_SEL_SPEED:
		SpeedDepthArrow.setVisible(false);
		SpeedArrow.setVisible(true);
		DepthArrow.setVisible(false);

		if(boConf)
		{
			boMenuActive = false;
			fdcan_stSCREEN_SEL_RAM.u32SelScreen = (uint32_t)fdcan_SEL_SPEED;
			application().gotoSpeedScreenNoTransition();
			fdcan_vScreenSel_Save();
		}
		break;

	case fdcan_SEL_DEPTH:
		SpeedDepthArrow.setVisible(false);
		SpeedArrow.setVisible(false);
		DepthArrow.setVisible(true);

		if(boConf)
		{
			boMenuActive = false;
			fdcan_stSCREEN_SEL_RAM.u32SelScreen = (uint32_t)fdcan_SEL_DEPTH;
			application().gotoDepthScreenNoTransition();
			fdcan_vScreenSel_Save();
		}
		break;

	default:
		break;
	}
	SpeedDepthArrow.invalidate();
	SpeedArrow.invalidate();
	DepthArrow.invalidate();
}
