#include <windows.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "CBreakoutGame.h"
#include "CBreakoutStateFactory.h"
#pragma comment (lib, "res/bin/Release/VerrevEngine2D.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(634);

	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_BTNFACE;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "Window";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(0, "Window", "VerrevBreakout", WS_OVERLAPPEDWINDOW, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0, 0, hInstance, 0);
	if (!windowHandle) return -1;

	ShowWindow(windowHandle, nCmdShow);

	{
		CBreakoutGame game;
		game.setStateFactory(new CBreakoutStateFactory);
		game.init(windowHandle);
		game.setState(VERREV_STATE::STATE_MENU);

		MSG msg;
		while (!GetAsyncKeyState(VK_ESCAPE)) {
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			game.update();
			game.draw();
		}
		game.destroy();
	}
	return 0;
}