#pragma once

#include "res/bin/Include/VerrevEngine2D.h"

class CBreakoutGame : public CGame
{
public:
	bool init(const HWND &window);
	void destroy();
	void update();
	void draw();
public:
	CD2DRenderer g;
	CInput i;
};