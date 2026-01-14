#include <gui/menu_screen/MenuView.hpp>
#include <gui/menu_screen/MenuPresenter.hpp>

MenuPresenter::MenuPresenter(MenuView& v)
    : view(v)
{

}

void MenuPresenter::activate()
{

}

void MenuPresenter::deactivate()
{

}

void MenuPresenter::SelScreen(fdcan_enSEL_SCREEN_t enArrow, bool boConf)
{
	view.SetupScreen(enArrow, boConf);
}
