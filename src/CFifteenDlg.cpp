#include "CFifteenDlg.h"

CFifteenDlg* CFifteenDlg::pCFifteenDlg = NULL;

CFifteenDlg::CFifteenDlg(HINSTANCE hInstance, Fifteen* game) : gtime(0)
{
	pCFifteenDlg = this;
	if (game)
	{
		fifteen = game;
	}
	else
	{
		MessageBox(NULL, TEXT("Не удалось запустить игру"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	hInst = hInstance;

	for(int i = 0; i < COUNT; i++)
	{
		idButtons[i] = START_ID + i;
	}
}

BOOL CFifteenDlg::CFifteenDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hNewGameButton = GetDlgItem(hwnd, IDC_NEWGAME);
	hNewGameButton = GetDlgItem(hwnd, IDC_EXIT);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS);
	hWindow = hwnd;
	
	MoveWindow(hwnd, 0, 0, BUTTON_WIDTH * SIZE + 60, BUTTON_HEIGTH * SIZE + 130, TRUE);
	
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			CreateWindow(
				TEXT("Button"), 
				TEXT(""), 
				WS_CHILD | WS_VISIBLE,
				i * BUTTON_WIDTH + OFFSET, 
				j * BUTTON_HEIGTH + OFFSET, 
				BUTTON_WIDTH, 
				BUTTON_HEIGTH, 
				hwnd, 
				(HMENU)idButtons[i + j * SIZE], 
				hInst, 
				NULL);
		}
	}

	HICON hIconSm, hIcon;
	hIconSm = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2));
	SetClassLong(hwnd, GCL_HICON, (LONG)hIcon);
	SetClassLong(hwnd, GCL_HICONSM, (LONG)hIconSm);
	
	MoveWindow(hProgress, OFFSET, BUTTON_HEIGTH * SIZE + OFFSET + 5, BUTTON_WIDTH * SIZE, 20, TRUE);
	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, TIME));
	SendMessage(hProgress, PBM_SETSTEP, 1, 0);
	SendMessage(hProgress, PBM_SETPOS, 0, 0);
		
	DrawField();

	return TRUE;
}

BOOL CALLBACK CFifteenDlg::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE,		 pCFifteenDlg->CFifteenDlg_OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND,	 pCFifteenDlg->CFifteenDlg_OnCommand);
		HANDLE_MSG(hWnd, WM_TIMER,		 pCFifteenDlg->CFifteenDlg_OnTimer);
		HANDLE_MSG(hWnd, WM_INITDIALOG,  pCFifteenDlg->CFifteenDlg_OnInitDialog);
	}

	return FALSE;
}

void CFifteenDlg::CFifteenDlg_OnCommand(HWND h, UINT id, HWND hwndCtr, UINT codeNotify)
{
	TCHAR mess[128] = TEXT("");
	switch (id)
	{
	case IDC_EXIT:
		EndDialog(h, 0);
		break;
	case IDC_NEWGAME:
		SetTimer(h, 1, 1000, 0);
		SendMessage(hProgress, PBM_SETPOS, 0, 0);
		gtime = 0;
		fifteen->FillField();
		do
		{
			fifteen->Shuffle();
		} while(fifteen->isWin());
		DrawField();
		break;
	default:
		if(gtime)
		{
			if( fifteen->MoveCell(id - START_ID) )
			{
				DrawField();
			}

			if( fifteen->isWin() )
			{
				KillTimer(h, 1);
				wsprintf(mess, TEXT("Собрано. Время: %d"), gtime); 
				MessageBox(h, mess, TEXT("Информация"), MB_OK);
			}
		}
		break;
	}
}

void CFifteenDlg::CFifteenDlg_OnTimer(HWND hwnd, UINT id)
{
	gtime++;
	TCHAR szTitle[128];
	wsprintf(szTitle, TEXT("Пятнашки %d сек"), gtime);
	SetWindowText(hwnd, szTitle);

	int pos = SendMessage(hProgress, PBM_GETPOS, 0, 0);
	if(pos == TIME)
	{
		KillTimer(hwnd, 1);
		MessageBox(hwnd, TEXT("Game Over"), TEXT("Information"), MB_OK);
		SendMessage(hProgress, PBM_SETPOS, 0, 0);
		gtime = 0;
	}
	else
	{
		SendMessage(hProgress, PBM_STEPIT, 0, 0);
	}
}

void CFifteenDlg::CFifteenDlg_OnClose(HWND h)
{
	KillTimer(h, 1);
	EndDialog(h, 0);
}

void CFifteenDlg::DrawField()
{
	std::vector<Cell> field = fifteen->GetField();
	std::vector<Cell>::iterator iter = field.begin();
	TCHAR text[8] = {0};
	for( int i = 0; iter != field.end(); iter++, i++)
	{
		(*iter).GetValue() ? wsprintf(text, TEXT("%d"), (*iter).GetValue()) : wsprintf(text, TEXT(" "));
		SetWindowText(GetDlgItem(hWindow, idButtons[i]), text); 
	}
}