#include "CConsoleState.h"
#include "CBreakoutGame.h"

void CConsoleState::onConsoleEnter()
{
	std::wstring s = ((CUIButton*)uielements[consoleHistory])->getText();
	if (s.length()) s += L"\n";
	std::wstring command = ((CUITextBox*)uielements[textBox])->getText();
	if (command.length()) {
		s += ((CUIButton*)uielements[consoleAnnotation])->getText();
		s += command;
		s += handleCommand(command);
		((CUIButton*)uielements[consoleHistory])->setText(s);
		((CUITextBox*)uielements[textBox])->setText(L"");
	}
	((CUITextBox*)uielements[textBox])->mIsWriting = 1;
	s = ((CUIButton*)uielements[consoleHistory])->getText();
	if (std::count(s.begin(), s.end(), '\n') >= lineCount) ((CUIButton*)uielements[consoleHistory])->setText(s.erase(0, s.find_first_of(L"\n") + 1));
	if (command == L"clr") ((CUIButton*)uielements[consoleHistory])->setText(L"");
}

std::wstring CConsoleState::handleCommand(const std::wstring &command)
{
	std::wstring result = L"";
	for (auto c : commands) result += c->hit(command);
	if (!result.size()) {
		result = L"\nError, command '";
		result += command;
		result += L"' not found.";
	}
	return result;
}

void CConsoleState::init(CGame *game, UINT_PTR data)
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);

	lineCount = 12;

	background = "menu-background";
	ga->g.addBitmap(background, L"c:/users/Vootele Verrev/downloads/back.jpg");

	ga->g.addSolidBrush("menu-brush", D2D1::ColorF(0.1f, 0.6f, 0.2f, 1.0f));
	ga->g.setBrush("menu-brush");

	ga->g.addFont("menu-font", L"Verdana", 15);
	ga->g.setFont("menu-font");

	// console
	titleBar = "console-title";
	UI_BUTTON_DESC bd{ titleBar, 10 ,10 ,90 + 400,20, D2D1::ColorF(1, 1, 1, 1), D2D1::ColorF(0, 0, 0, 1), L"CONSOLE" , 12};
	uielements[titleBar] = new CUIButton;
	uielements[titleBar]->init(&ga->g, &bd);

	bd.centerH = false;
	bd.centerV = false;
	consoleHistory = "console-history";
	bd.id = consoleHistory;
	bd.text = L"sudo apt-get install apache2\nsudo apt-get upgrade";
	bd.x = 10; bd.y += bd.h + 1;
	bd.w = 90 + 400; bd.h = 200;
	uielements[consoleHistory] = new CUIButton;
	uielements[consoleHistory]->init(&ga->g, &bd);

	consoleAnnotation = "console-annotation-label";
	bd.text = L"root@verrev:~$ ";
	bd.y += bd.h + 1;
	bd.w = 90; bd.h = 20;
	uielements[consoleAnnotation] = new CUIButton;
	uielements[consoleAnnotation]->init(&ga->g, &bd);

	textBox = "textbox";
	UI_TEXTBOX_DESC td{ textBox, bd.x + bd.w, bd.y ,400,bd.h, D2D1::ColorF(1, 1, 1, 1), D2D1::ColorF(0, 0, 0, 1), L"", 12, std::bind(&CConsoleState::onConsoleEnter, this), false, false };
	uielements[textBox] = new CUITextBox;
	uielements[textBox]->init(&ga->g, &td);
	ga->i.registerObserver((CUITextBox*)(uielements[textBox]));

	commands.push_back(new CHelpCommand(L"help"));
	commands.push_back(new CGetTimeCommand(L"time"));

}

void CConsoleState::destroy(CGame *game)
{
	for (auto i = uielements.begin(); i != uielements.end(); ++i) delete i->second;
	uielements.clear();
}

void CConsoleState::update(CGame *game)
{
}

void CConsoleState::draw(CGame *game)
{
	CBreakoutGame *ga = static_cast<CBreakoutGame*>(game);
	ga->g.drawBitmap(background, 0, 0);
	for (auto i = uielements.begin(); i != uielements.end(); ++i) i->second->draw();
}
