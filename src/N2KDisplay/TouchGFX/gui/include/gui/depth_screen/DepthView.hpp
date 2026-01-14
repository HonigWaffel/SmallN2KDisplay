#ifndef DEPTHVIEW_HPP
#define DEPTHVIEW_HPP

#include <gui_generated/depth_screen/DepthViewBase.hpp>
#include <gui/depth_screen/DepthPresenter.hpp>

class DepthView : public DepthViewBase
{
public:
    DepthView();
    virtual ~DepthView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateDepth(float d);
    virtual void setDarkMode(bool enable);
    virtual void changeScreen(uint8_t u8NewScreen);
protected:
};

#endif // DEPTHVIEW_HPP
