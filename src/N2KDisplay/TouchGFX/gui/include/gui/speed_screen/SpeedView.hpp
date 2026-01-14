#ifndef SPEEDVIEW_HPP
#define SPEEDVIEW_HPP

#include <gui_generated/speed_screen/SpeedViewBase.hpp>
#include <gui/speed_screen/SpeedPresenter.hpp>

class SpeedView : public SpeedViewBase
{
public:
    SpeedView();
    virtual ~SpeedView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateSpeed(float v);
    virtual void setDarkMode(bool enable);
    virtual void changeScreen(uint8_t u8NewScreen);
protected:
};

#endif // SPEEDVIEW_HPP
