#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateSpeed(float v);
    virtual void updateDepth(float d);
    virtual void setDarkMode(bool enable);
    virtual void changeScreen(uint8_t u8NewScreen);

protected:

};

#endif // SCREEN1VIEW_HPP
