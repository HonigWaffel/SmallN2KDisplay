#include <gui/depth_screen/DepthView.hpp>
#include <cstdio>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Color.hpp>

DepthView::DepthView()
{

}

void DepthView::setupScreen()
{
    DepthViewBase::setupScreen();
    DepthTarget.setWildcard(DepthTargetBuffer);
}

void DepthView::tearDownScreen()
{
    DepthViewBase::tearDownScreen();
}

void DepthView::updateDepth(float d)
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

void DepthView::setDarkMode(bool enable)
{
    if (enable) {
        // Dark Mode: schwarzer BG, weiße Texte
        BackGround.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz

        DepthLabel.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        DepthTarget.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
        Depth_Unit.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß
    }
    else
    {
        // Normal Mode: Originalfarben zurück
        BackGround.setColor(Color::getColorFromRGB(255, 255, 255)); // Weiß

        DepthLabel.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        DepthTarget.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
        Depth_Unit.setColor(Color::getColorFromRGB(0, 0, 0));      // Schwarz
    }

    // Neuzeichnen
    BackGround.invalidate();
    DepthTarget.invalidate();
    Depth_Unit.invalidate();
}

void DepthView::changeScreen(uint8_t u8NewScreen)
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
