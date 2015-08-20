#include "CBreakoutGame.h"
#include "CGameState.h"

bool CBreakoutGame::init(const HWND &window)
{
	if (!g.init(window)) return 0;
	i.mWindow = window;
	return 1;
}

void CBreakoutGame::destroy()
{
	mStateMachine.removeCurState(this);
	delete mStateFactory;
}

void CBreakoutGame::update()
{
	i.update();
	mStateMachine.mCurState->update(this);
}

void CBreakoutGame::draw()
{
	g.beginDraw();
	mStateMachine.mCurState->draw(this);
	g.endDraw();
}