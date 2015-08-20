#pragma once

#include <windows.h>
#include <vector>

#include "res/bin/Include/VerrevEngine2D.h"
#include "res/bin/Include/CState.h"

class CGame;

class Brick
{
public:
	Brick(const D2D1_RECT_F &r, const std::string &b) : coords(r), brush(b) {}
	virtual ~Brick() {}
	D2D1_RECT_F coords;
	std::string brush;
};

class CGameState : public CState
{
public:
	CGameState() {}
	~CGameState() {}
	void init(CGame *game, UINT_PTR data = 0) override;
	void destroy(CGame *game) override;
	void update(CGame *game) override;
	void draw(CGame *game) override;
	void onClick()
	{
		MessageBoxA(0, "Clicked!", "", 0);
	}
	void onEnter()
	{
		std::string s = std::string(textbox.getText().begin(), textbox.getText().end());
		MessageBoxA(0, s.c_str(), "", 0);
	}
private:
	float ballX, ballY, ballRadius, speedX, speedY;
	float paddleX, paddleY, paddleW, paddleH;
	D2D1_RECT_F ballBoundingBox, paddleBoundingBox;
	std::string background;
	std::vector<Brick*> bricks;
	int score, lives;
	CUIButton button;
	CUICheckBox checkbox;
	CUITextBox textbox;
};

