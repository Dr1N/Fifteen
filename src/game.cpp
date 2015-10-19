#pragma once
#include "mystdafx.h"
#include "CFifteenDlg.h"
#include "FifteenGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR szCmdLine,
				   int iCmdShow)
{
	srand((unsigned int)time(0));
	Fifteen fiften;
	CFifteenDlg dlg(hInstance, &fiften);
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_FIFTEEN), NULL, CFifteenDlg::DlgProc);
}