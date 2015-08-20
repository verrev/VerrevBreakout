#pragma once

#include <windows.h>
#include "res/bin/Include/CStateFactory.h"
#include "res/bin/Include/CState.h"

enum VERREV_STATE
{
	STATE_GAME,
	STATE_MENU,
	STATE_CONSOLE
};

class CBreakoutStateFactory : public CStateFactory
{
public:
	CState *getState(const UINT &id) const override;
};