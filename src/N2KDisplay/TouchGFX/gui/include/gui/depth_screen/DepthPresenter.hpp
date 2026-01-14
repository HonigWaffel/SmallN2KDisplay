#ifndef DEPTHPRESENTER_HPP
#define DEPTHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DepthView;

class DepthPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DepthPresenter(DepthView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~DepthPresenter() {}

    virtual void DepthN2kValue(fdcan_enn2kDATA_t type, float value, uint32_t u32Screen);

private:
    DepthPresenter();

    DepthView& view;
};

#endif // DEPTHPRESENTER_HPP
