#pragma once

#include <windows.h>
#include <vector>
#include <map>

#include "res/bin/Include/CState.h"
#include "res/bin/Include/VerrevEngine2D.h"
#include "CHelpCommand.h"
#include "CGetTimeCommand.h"
#include "CBreakoutStateFactory.h"

class CGame;
class CConsoleCommand;

class CConsoleState : public CState
{
public:
	CConsoleState() {}
	~CConsoleState() {}
	void init(CGame *game, UINT_PTR data = 0) override;
	void destroy(CGame *game) override;
	void update(CGame *game) override;
	void draw(CGame *game) override;

	void onConsoleEnter();
	std::wstring handleCommand(const std::wstring &command);
private:
	std::map <std::string, CUIElement*> uielements;
	std::string background;
	std::string consoleHistory, textBox, titleBar, consoleAnnotation;
	int mStatus = 0;
	int lineCount;
	std::vector<CConsoleCommand*> commands;
};

