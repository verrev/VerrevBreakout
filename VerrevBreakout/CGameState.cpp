#include "CGameState.h"
#include "CBreakoutGame.h"
#include "CBreakoutStateFactory.h"
#include <ctime>

bool valueInRange(float value, float min, float max)
{
	return (value >= min) && (value <= max);
}

bool collided(const D2D1_RECT_F &a, const D2D1_RECT_F &b, D2D1_POINT_2F &point = D2D1::Point2F(0, 0))
{
	bool xOverlap = valueInRange(a.left, b.left, b.left + (b.right - b.left)) ||
		valueInRange(b.left, a.left, a.left + (a.right - a.left));
	bool yOverlap = valueInRange(a.top, b.top, b.top + (b.bottom - b.top)) ||
		valueInRange(b.top, a.top, a.top + (a.bottom - a.top));
	return xOverlap && yOverlap;
}

void CGameState::init(CGame *game, UINT_PTR data) 
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);

	ballX = 400 - ballRadius, ballY = 600 - ballRadius - 20, ballRadius = 19, speedY = 2 * 5.0f, speedX = 2 * 2.0f;
	paddleX = 400, paddleY = 600 - 10, paddleW = 150, paddleH = 10;
	score = 0;
	lives = 3;

	background = "game-background";
	ga->g.addBitmap(background, L"back2.jpg");

	ga->g.addSolidBrush("game-brush", D2D1::ColorF(0.2f, 0.8f, 0.3f, 1.0f));
	ga->g.setBrush("game-brush");

	std::vector<std::string> brushes;
	brushes.push_back("brick-brush1");
	brushes.push_back("brick-brush2");
	brushes.push_back("brick-brush3");
	brushes.push_back("brick-brush4");
	brushes.push_back("brick-brush5");
	brushes.push_back("brick-brush6");
	brushes.push_back("brick-brush7");

	ga->g.addSolidBrush(brushes.at(0), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	ga->g.addSolidBrush(brushes.at(1), D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));
	ga->g.addSolidBrush(brushes.at(2), D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f));
	ga->g.addSolidBrush(brushes.at(3), D2D1::ColorF(0.0f, 0.0f, 1.0f, 1.0f));
	ga->g.addSolidBrush(brushes.at(4), D2D1::ColorF(0.4f, 0.6f, 0.7f, 1.0f));
	ga->g.addSolidBrush(brushes.at(5), D2D1::ColorF(0.1f, 0.8f, 0.2f, 1.0f));
	ga->g.addSolidBrush(brushes.at(6), D2D1::ColorF(0.2f, 0.4f, 0.3f, 1.0f));

	srand(time(0));

	ga->g.addFont("game-font", L"Consolas", 25);
	ga->g.setFont("game-font");

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 10; ++j) {
			float x = i * 39.5 + 5;
			float y = j * 25 + 5;
			float x2 = x + 35.5;
			float y2 = y + 20;
			bricks.push_back(new Brick(D2D1::RectF(x, y, x2, y2), brushes.at(rand() % 6)));
		}
	}
}

void CGameState::destroy(CGame *game) 
{
	for (auto a : bricks) delete a;
}

void CGameState::update(CGame *game) 
{
	ballX += speedX;
	ballY += speedY;

	ballBoundingBox = D2D1::RectF(ballX - ballRadius, ballY - ballRadius, ballX + ballRadius, ballY + ballRadius);
	paddleBoundingBox = D2D1::RectF(paddleX, paddleY, paddleX + paddleW, paddleY + paddleH);

	if (ballX - ballRadius < 0 || ballX + ballRadius > 800) speedX = -speedX;
	if (ballY - ballRadius < 0) speedY = -speedY;

	if (ballY + ballRadius > 600) {
		if (collided(ballBoundingBox, paddleBoundingBox)) {
			speedY = -speedY;
		}
		else {
			if (--lives == 0) {
				game->setState(VERREV_STATE::STATE_MENU);
			}
			ballX = 400 - ballRadius, ballY = 600 - ballRadius - 20, speedY = -speedY, speedX -= speedX;
		}
	}
	for (int i = 0; i < bricks.size(); ++i) {
		if (collided(bricks.at(i)->coords, ballBoundingBox)) {
			bricks.erase(bricks.begin() + i);
			speedX = -speedX;
			speedY = -speedY;
			++score;
			break;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) && paddleX > 0) {
		paddleX -= 9.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT) && paddleX + paddleW < 800) {
		paddleX += 9.0f;
	}
}

void CGameState::draw(CGame *game)
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);
	ga->g.drawBitmap(background, 0, 0);
	ga->g.fillCircle(ballX, ballY, ballRadius);
	ga->g.fillRect(paddleX, paddleY, paddleW, paddleH);
	for (auto r : bricks) ga->g.fillRect(r->coords.left, r->coords.top, r->coords.right - r->coords.left, r->coords.bottom - r->coords.top, r->brush);

	std::string scoreText = "Score: " + std::to_string(score);
	std::wstring wsTmp(scoreText.begin(), scoreText.end());
	ga->g.drawText(wsTmp, 0, 0, 800, 600);
}
