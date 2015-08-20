#include "CMenuState.h"
#include "CBreakoutGame.h"

void CMenuState::init(CGame *game, UINT_PTR data)
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);

	ga->g.addBitmap(background, L"back2.jpg");
	ga->g.addSolidBrush("menu-brush", D2D1::ColorF(0.1f, 0.6f, 0.2f, 1.0f));
	ga->g.setBrush("menu-brush");
	ga->g.addFont("menu-font", L"Verdana", 15);
	ga->g.setFont("menu-font");

	playButton = "play-button";	
	UI_BUTTON_DESC bd(playButton, 800 / 2 - 50, 600 / 2 - 30, 100, 20, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), L"Play", 15.0f, std::bind(&CMenuState::onPlayClick, this));
	uielements[playButton] = new CUIButton;
	uielements[playButton]->init(&ga->g, &bd);
	ga->i.registerObserver((CUIButton*)(uielements[playButton]));

	exitButton = "exit-button";
	UI_BUTTON_DESC bd2(exitButton, 800 / 2 - 50, 600 / 2 - 30 + 20 + 5, 100, 20, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), L"Exit", 15.0f, std::bind(&CMenuState::onExitClick, this));
	uielements[exitButton] = new CUIButton;
	uielements[exitButton]->init(&ga->g, &bd2);
	ga->i.registerObserver((CUIButton*)(uielements[exitButton]));
}

void CMenuState::destroy(CGame *game)
{
	for (auto i = uielements.begin(); i != uielements.end(); ++i) delete i->second;
	uielements.clear();
}

void CMenuState::update(CGame *game)
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);
	if (mStatus == 1) {
		ga->i.unRegisterObserver((CUIButton*)(uielements[playButton]));
		ga->i.unRegisterObserver((CUIButton*)(uielements[exitButton]));
		game->setState(VERREV_STATE::STATE_GAME);
	}
	else if (mStatus == -1) {
		ga->i.unRegisterObserver((CUIButton*)(uielements[playButton]));
		ga->i.unRegisterObserver((CUIButton*)(uielements[exitButton]));
		ga->destroy();
		PostQuitMessage(0);
		exit(0);
	}
}

void CMenuState::draw(CGame *game)
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);

	ga->g.drawBitmap(background, 0, 0);
	ga->g.drawText(L"VERREV BREAKOUT 2015", 0, 10, ga->g.getRenderTarget()->GetSize().width, 10);
	for (auto i = uielements.begin(); i != uielements.end(); ++i) i->second->draw();
}
