#include "CBreakoutStateFactory.h"
#include "CGameState.h"
#include "CMenuState.h"
#include "CConsoleState.h"

CState *CBreakoutStateFactory::getState(const UINT &id) const
{
	if (id == VERREV_STATE::STATE_GAME) {
		return new CGameState;
	}
	else if (id == VERREV_STATE::STATE_MENU) {
		return new CMenuState;
	}
	else if (id == VERREV_STATE::STATE_CONSOLE) {
		return new CConsoleState;
	}
	return nullptr;
}