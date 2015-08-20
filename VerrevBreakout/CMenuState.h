#pragma once

#include <windows.h>
#include <vector>
#include <map>

#include "res/bin/Include/VerrevEngine2D.h"
#include "res/bin/Include/CState.h"
#include "CBreakoutStateFactory.h"

class CGame;

class CMenuState : public CState
{
public:
	CMenuState() {}
	~CMenuState() {}
	void init(CGame *game, UINT_PTR data = 0) override;
	void destroy(CGame *game) override;
	void update(CGame *game) override;
	void draw(CGame *game) override;
	void onPlayClick()
	{
		mStatus = 1;
	}
	void onExitClick()
	{
		mStatus = -1;
	}
	void onEnter()
	{
		//std::string s = std::string(((CUITextBox*)uielements["textBox"])->getText().begin(), ((CUITextBox*)uielements[""])->getText().end());
		//MessageBoxA(0, s.c_str(), "", 0);
	}
private:
	std::map <std::string, CUIElement*> uielements;
	std::string background;
	std::string playButton, exitButton;
	int mStatus = 0;
};

