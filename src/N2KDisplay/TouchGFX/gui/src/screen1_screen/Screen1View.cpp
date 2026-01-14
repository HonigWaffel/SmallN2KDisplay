#include <gui/screen1_screen/Screen1View.hpp>
#include <cstdio>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Color.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    SpeedTarget.setWildcard(SpeedTargetBuffer);
    DepthTarget.setWildcard(DepthTargetBuffer);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateSpeed(float v)
{
    Unicode::snprintfFloat(SpeedTargetBuffer, SPEEDTARGET_SIZE, "%.2f", v);
    SpeedTarget.invalidate();
}

void Screen1View::updateDepth(float d)
{
	if (d > 655.0f)
	{
	    Unicode::snprintfFloat(DepthTargetBuffer, DEPTHTARGET_SIZE, "---", d);
	}
	else
	{
	    Unicode::snprintfFloat(DepthTargetBuffer, DEPTHTARGET_SIZE, "%.2f", d);
	}
    DepthTarget.invalidate();
}

void Screen1View::setDarkMode(bool enable)
{
    if (enable) {
        // Dark Mode: schwarzer BG, weiße Texte
        BackGround.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz

        SpeedLabel.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        DepthLabel.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        SpeedTarget.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        DepthTarget.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        Depth_Unit.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
		Speed_Unit.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß

		line1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		line1.setPainter(line1Painter);
    }
    else
    {
        // Normal Mode: Originalfarben zurück
        BackGround.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß

        SpeedLabel.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        DepthLabel.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        SpeedTarget.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        DepthTarget.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        Depth_Unit.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
		Speed_Unit.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz

		line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		line1.setPainter(line1Painter);
    }

    // Neuzeichnen
    BackGround.invalidate();
    SpeedTarget.invalidate();
    DepthTarget.invalidate();
    Depth_Unit.invalidate();
	Speed_Unit.invalidate();
	line1.invalidate();
}

void Screen1View::changeScreen(uint8_t u8NewScreen)
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
