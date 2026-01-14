#include <gui/speed_screen/SpeedView.hpp>
#include <cstdio>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Color.hpp>

SpeedView::SpeedView()
{

}

void SpeedView::setupScreen()
{
    SpeedViewBase::setupScreen();
    SpeedTarget.setWildcard(SpeedTargetBuffer);
}

void SpeedView::tearDownScreen()
{
    SpeedViewBase::tearDownScreen();
}

void SpeedView::updateSpeed(float v)
{
    Unicode::snprintfFloat(SpeedTargetBuffer, SPEEDTARGET_SIZE, "%.2f", v);
    SpeedTarget.invalidate();
}

void SpeedView::setDarkMode(bool enable)
{
    if (enable) {
        // Dark Mode: schwarzer BG, weiße Texte
        BackGround.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz

        SpeedLabel.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        SpeedTarget.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
		Speed_Unit.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
    }
    else
    {
        // Normal Mode: Originalfarben zurück
        BackGround.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß

        SpeedLabel.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        SpeedTarget.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
		Speed_Unit.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
    }

    // Neuzeichnen
    BackGround.invalidate();
    SpeedTarget.invalidate();
	Speed_Unit.invalidate();
}

void SpeedView::changeScreen(uint8_t u8NewScreen)
{
	static uint8_t u8OldScreen = 0;

	if(u8NewScreen != u8OldScreen)
	{
		switch(u8NewScreen)
		{
		case fdcan_SEL_SCREEN1:
			application().gotoScreen1ScreenNoTransition();
			break;
		case fdcan_SEL_SPEED:
			application().gotoSpeedScreenNoTransition();
			break;
		case fdcan_SEL_DEPTH:
			application().gotoDepthScreenNoTransition();
			break;
		case fdcan_SEL_MENUS:
			application().gotoMenuScreenNoTransition();
			break;
		default:
			break;
		}
	}
}
