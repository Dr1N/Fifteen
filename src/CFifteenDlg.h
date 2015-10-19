#pragma once
#include "mystdafx.h"
#include "FifteenGame.h"

class CFifteenDlg
{
private:
	Fifteen* fifteen;
	HINSTANCE hInst;								
	HWND hWindow;
	int  idButtons[COUNT];
	HWND hNewGameButton;
	HWND hExitButton;
	HWND hProgress;
	int gtime;

	BOOL CFifteenDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void CFifteenDlg_OnClose(HWND h);
	void CFifteenDlg_OnCommand(HWND h, UINT id, HWND hwndCtr, UINT codeNotify);
	void CFifteenDlg_OnTimer(HWND hwnd, UINT id);
	void DrawField();
	static CFifteenDlg* pCFifteenDlg;

public:
	CFifteenDlg(HINSTANCE hInstance, Fifteen* game);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};