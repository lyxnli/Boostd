#include <iostream>
#include <Windows.h>
#include "resource.h"
#include <ShlObj.h>
#include <ShlObj_core.h>
#include <fstream>

// ######
// #     # #####   ####  #####  ####  ##### #   # #####  ######  ####  
// #     # #    # #    #   #   #    #   #    # #  #    # #      #      
// ######  #    # #    #   #   #    #   #     #   #    # #####   ####
// #       #####  #    #   #   #    #   #     #   #####  #           # 
// #       #   #  #    #   #   #    #   #     #   #      #      #    # 
// #       #    #  ####    #    ####    #     #   #      ######  ####  

#define EXECUTE_RUN 1
#define UPDATE_PROGRAMS 2
#define EXIT_PROGRAM 3
#define CHANGE_WIN_TITLE 4
#define RESET_WIN_TITLE 5
#define ADD_TO_MSGBOX 6
#define EXECUTE_REGEDIT 7
#define EXECUTE_CMD 8
#define EXECUTE_TASKMGR 9
#define BYPASS_WIN11CHECKS 10
#define CLEAN_WINDOW_OPEN 11
#define SYS_WINDOW_OPEN 12
#define WIFI_WINDOW_OPEN 13
#define MADE_BY 14

//Adds the "new" style to the buttons
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Window Procedure function
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
// Adds the menus to the window
void AddMenus(HWND hWnd);
// Adds Contorls to the window
void AddControls(HWND hWnd);
// Menu handler
HMENU hMenu;
// Edit Handler
HWND hEdit;
// Font

HFONT hFont;

// Clean sub-window
void regCleanClass(HINSTANCE);
// Displays the window of Clean
void displayCleanWindow(HWND);

// Sys sub-window
void regSysClass(HINSTANCE);
// Displays the window of Sys
void displaySysWindow(HWND);

// Wifi sub-window
void regWifiClass(HINSTANCE);
// Displays the window of Wifi
void displayWifiWindow(HWND);

// Made BY sub-window
void regMadebyClass(HINSTANCE);
// Displays the window of Made By
void displayMadebyWindow(HWND);

// #######                                                   
// #       #    # #    #  ####  ##### #  ####   #    #  ####  
// #       #    # ##   # #    #   #   # #    #  ##   # #      
// #####   #    # # #  # #        #   # #    #  # #  #  ####
// #       #    # #  # # #        #   # #    #  #  # #      # 
// #       #    # #   ## #    #   #   # #    #  #   ## #    # 
// #        ####  #    #  ####    #   #  ####   #    #  ####  


std::string profilePath() {
	TCHAR path[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, path);
	std::string returnvar = path;
	returnvar += "\\";
	return returnvar;
}

std::string theProfilePath = profilePath();
// #     #                     #####  #     # ### 
// ##   ##   ##   # #    #    #     # #     #  #
// # # # #  #  #  # ##   #    #       #     #  #  
// #  #  # #    # # # #  #    #  #### #     #  #  
// #     # ###### # #  # #    #     # #     #  #  
// #     # #    # # #   ##    #     # #     #  #  
// #     # #    # # #    #     #####   #####  ### 



// Needs the int main function or visual studio goes haywire -_-
// Also needs Properties -> Linker -> System -> SubSystem needs to be changed to WINDOWS -_-
int main() {}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	// Class to hold the window
	WNDCLASSW wc = { 0 };
	// Alows the window to have color
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	// Allows you to see your cursor
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Defines the hInst the window should be connected to
	wc.hInstance = hInst;
	// Defines the class name of the window
	wc.lpszClassName = L"mainWindowClass";
	// Defines the window procedure function to be used
	wc.lpfnWndProc = WindowProcedure;
	// Adds a icon
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClassW(&wc)) {
		MessageBoxA(NULL, "Register Failed", "Register Failed", MB_OK);
	}
	regCleanClass(hInst);
	regSysClass(hInst);
	regWifiClass(hInst);
	regMadebyClass(hInst);

	CreateWindowW(L"mainWindowClass", L"Boostd", WS_SYSMENU | WS_VISIBLE, 625, 300, 700, 500, NULL, NULL, NULL, NULL);


	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}
void setFont() {
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	hFont = CreateFontIndirect(&ncm.lfMessageFont);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	bool ud = TRUE;
	switch (msg)
	{
		break;
	case WM_CHAR:
	{
		if (wp == VK_ESCAPE && ud == TRUE) {
			MessageBox(hWnd, "hello", "hello", MB_OK);
			
			ShowWindow(GetConsoleWindow(), SW_HIDE);
			ud = FALSE;
		}

	}
		break;
	case WM_COMMAND:
		
		switch (wp)
		{
		case MADE_BY:
			displayMadebyWindow(hWnd);
			break;
		case CLEAN_WINDOW_OPEN:
			displayCleanWindow(hWnd);
			break;
		case SYS_WINDOW_OPEN:
			displaySysWindow(hWnd);
			break;
		case WIFI_WINDOW_OPEN:
			displayWifiWindow(hWnd);
			break;
		case EXECUTE_RUN:
			system("explorer shell:::{2559a1f3-21d7-11d4-bdaf-00c04f60b9f0}");
			break;
		case EXECUTE_CMD:
			system("cmd");
			break;
		case EXECUTE_TASKMGR:
			system("taskmgr");
			break;
		case EXECUTE_REGEDIT:
			system("regedit");
			break;
		case BYPASS_WIN11CHECKS:
			break;
		case UPDATE_PROGRAMS: {
			int UdMsgBox = MessageBoxW(hWnd, L"Are you sure you want to update all programs?", L"Update?", MB_YESNO | MB_ICONQUESTION);
			if (UdMsgBox == IDYES) {
				AllocConsole();
				system("echo Updating all programs. && echo Do not close this window! Press Ctrl+C to cancel updating && echo --------------------------");
				ud = TRUE;
				system("winget upgrade --all");
			}
		}
			break;
		
		case EXIT_PROGRAM: {
			int ExitMsgBox = MessageBoxW(hWnd, L"Are you sure you want to leave?", L"Leave?", MB_YESNO | MB_ICONQUESTION);
			if (ExitMsgBox == IDYES) {
				DestroyWindow(hWnd);
			}
		}
			break;
			// Add {} everytime you make a var in a switch
			// Casting is VERY helpful :)	
		}
		break;
	case WM_CREATE:
		setFont();
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}


void AddMenus(HWND hWnd) {
	// Creates a menu
	hMenu = CreateMenu();
	// Adds a dropdown menu
	HMENU hFileDropDown = CreateMenu();
	HMENU hToolsDropDown = CreateMenu();
	// Adds items to the dropdown menu
	AppendMenu(hToolsDropDown, MF_STRING, EXECUTE_RUN, "Run");
	AppendMenu(hToolsDropDown, MF_STRING, UPDATE_PROGRAMS, "Update Programs");
	AppendMenu(hToolsDropDown, MF_STRING, EXECUTE_CMD, "Command Prompt");
	AppendMenu(hToolsDropDown, MF_STRING, EXECUTE_REGEDIT, "Regedit");
	AppendMenu(hToolsDropDown, MF_STRING, EXECUTE_TASKMGR, "Task Manager");
	

	AppendMenu(hFileDropDown, MF_STRING, MADE_BY, "Made By");
	// Separator
	AppendMenu(hFileDropDown, MF_SEPARATOR, NULL, NULL);

	AppendMenu(hFileDropDown, MF_STRING, EXIT_PROGRAM, "Exit");
	// Sub Drop Down Menu
	// Adds an item to the menu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileDropDown, "File");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hToolsDropDown, "Tools");
	//Adds it to the window
	SetMenu(hWnd, hMenu);
}

// Adds controls to the window (text input boxes, text boxes, etc.)
void AddControls(HWND hWnd) {
	//Adds a button or a static object through CreateWindowW
	HWND fontDlg = CreateWindowEx(NULL, "static", "Actions", WS_VISIBLE | WS_CHILD, 310, 125, 95, 50, hWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	// Buttons
	fontDlg = CreateWindowEx(NULL, "Button", "Clean", WS_VISIBLE | WS_CHILD, 110, 155, 140, 50, hWnd, (HMENU)CLEAN_WINDOW_OPEN, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "System Health Check", WS_VISIBLE | WS_CHILD, 255, 155, 150, 50, hWnd, (HMENU)SYS_WINDOW_OPEN, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Wifi Clean", WS_VISIBLE | WS_CHILD, 410, 155, 140, 50, hWnd, (HMENU)WIFI_WINDOW_OPEN, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);
}



// #     #                         ######        
// ##   ##   ##   #####  ######    #     # #   #
// # # # #  #  #  #    # #         #     #  # #  
// #  #  # #    # #    # #####     ######    #   
// #     # ###### #    # #         #     #   #   
// #     # #    # #    # #         #     #   #   
// #     # #    # #####  ######    ######    #   


#define DESTROY_WINDOW_MADEBY 1

LRESULT CALLBACK madebyWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND: {
		switch (wp)
		{
		case DESTROY_WINDOW_MADEBY:
			DestroyWindow(hWnd);
			break;
		}
	}
				   break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void regMadebyClass(HINSTANCE hInst) {
	WNDCLASSW wcc = { 0 };

	wcc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcc.hInstance = hInst;
	wcc.lpszClassName = L"madebyWindowClass";
	wcc.lpfnWndProc = madebyWindowProcedure;
	wcc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassW(&wcc);
}

void displayMadebyWindow(HWND hWnd) {
	HWND hMadebyWnd = CreateWindowW(L"madebyWindowClass", L"Made By", WS_VISIBLE, 650, 320, 500, 400, hWnd, NULL, NULL, NULL);
	setFont();
	HBITMAP bmp = (HBITMAP)LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 20, 20, NULL);
	HWND fontDlg = CreateWindowEx(NULL, "Button", "Close", WS_VISIBLE | WS_CHILD, 50, 275, 75, 50, hMadebyWnd, (HMENU)DESTROY_WINDOW_MADEBY, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);
}


//  #####                              
// #     #  #      ######   ##   #    # 
// #        #      #       #  #  ##   # 
// #        #      #####  #    # # #  # 
// #        #      #      ###### #  # # 
// #     #  #      #      #    # #   ## 
//  #####   ###### ###### #    # #    #

#define DESTROY_WINDOW_CLEAN 1
#define CLEAN_NOW 2
#define CLEAN_ALL_NOW 3
#define TMPFILES_ON 4
#define TMPFILES_OFF 5
#define THUMBNAILS_ON 6
#define THUMBNAILS_OFF 7
#define SYSTMPFILES_ON 8
#define SYSTMPFILES_OFF 9
bool tmpFiles = FALSE;
bool thumbnails = FALSE;
bool sysTmpFiles = FALSE;
void clean(HWND hWnd);

LRESULT CALLBACK cleanWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND: {
		switch (wp)
		{
		case DESTROY_WINDOW_CLEAN:
			DestroyWindow(hWnd);
			break;
		case CLEAN_NOW:
			clean(hWnd);
			break;
		case CLEAN_ALL_NOW:
			tmpFiles = TRUE;
			thumbnails = TRUE;
			sysTmpFiles = TRUE;
			clean(hWnd);
			break;
		case TMPFILES_ON:
			tmpFiles = TRUE;
			break;
		case THUMBNAILS_ON:
			thumbnails = TRUE;
			break;
		case SYSTMPFILES_ON:
			sysTmpFiles = TRUE;
			break;
		case TMPFILES_OFF:
			tmpFiles = FALSE;
			break;
		case THUMBNAILS_OFF:
			thumbnails = FALSE;
			break;
		case SYSTMPFILES_OFF:
			sysTmpFiles = FALSE;
			break;
		}
	}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void regCleanClass(HINSTANCE hInst) {
	WNDCLASSW wcc = { 0 };

	wcc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcc.hInstance = hInst;
	wcc.lpszClassName = L"cleanWindowClass";
	wcc.lpfnWndProc = cleanWindowProcedure;
	wcc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassW(&wcc);
}

void displayCleanWindow(HWND hWnd) {
	HWND hCleanWnd = CreateWindowW(L"cleanWindowClass", L"Clean", WS_VISIBLE, 650, 320, 500, 400, hWnd, NULL, NULL, NULL);
	setFont();
	HWND fontDlg = CreateWindowEx(NULL, "Button", "Cancel", WS_VISIBLE | WS_CHILD, 50, 275, 75, 50, hCleanWnd, (HMENU)DESTROY_WINDOW_CLEAN, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);


	// TMP FILES
	fontDlg = CreateWindowEx(NULL, "Button", "On", WS_VISIBLE | WS_CHILD, 50, 25, 50, 50, hCleanWnd, (HMENU)TMPFILES_ON, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Off", WS_VISIBLE | WS_CHILD, 100, 25, 50, 50, hCleanWnd, (HMENU)TMPFILES_OFF, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "static", "Temp Files", WS_VISIBLE | WS_CHILD, 175, 40, 95, 50, hCleanWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	// THUMBNAILS
	fontDlg = CreateWindowEx(NULL, "Button", "On", WS_VISIBLE | WS_CHILD, 50, 100, 50, 50, hCleanWnd, (HMENU)THUMBNAILS_ON, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Off", WS_VISIBLE | WS_CHILD, 100, 100, 50, 50, hCleanWnd, (HMENU)THUMBNAILS_OFF, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "static", "Thumbnails", WS_VISIBLE | WS_CHILD, 175, 115, 95, 50, hCleanWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	// SYS TEMP FILES
	fontDlg = CreateWindowEx(NULL, "Button", "On", WS_VISIBLE | WS_CHILD, 50, 175, 50, 50, hCleanWnd, (HMENU)SYSTMPFILES_ON, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Off", WS_VISIBLE | WS_CHILD, 100, 175, 50, 50, hCleanWnd, (HMENU)SYSTMPFILES_OFF, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "static", "System Temp Files", WS_VISIBLE | WS_CHILD, 175, 190, 150, 50, hCleanWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);



	fontDlg = CreateWindowEx(NULL, "Button", "Clean", WS_VISIBLE | WS_CHILD, 275, 275, 75, 50, hCleanWnd, (HMENU)CLEAN_NOW, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Clean All", WS_VISIBLE | WS_CHILD, 350, 275, 75, 50, hCleanWnd, (HMENU)CLEAN_ALL_NOW, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);
}


void clean(HWND hWnd) {
	if (tmpFiles == TRUE) {
		return;
	}
	else if (thumbnails == TRUE) {
		return;
	}
	else if (sysTmpFiles == TRUE) {
		return;
	}
	else {
		MessageBoxW(hWnd, L"Please set one of the options to true.", L"Boostd", MB_OK | MB_ICONERROR);
	}
}





//  #####                                   
// #     # #   #  ####  ##### ###### #    # 
// #        # #  #        #   #      ##  ## 
//  #####    #    ####    #   #####  # ## #
//       #   #        #   #   #      #    # 
// #     #   #   #    #   #   #      #    # 
//  #####    #    ####    #   ###### #    #

#define DESTROY_WINDOW_SYS 1
#define CLEAN_NOW 2
#define CLEAN_ALL_NOW 3
#define TMPFILES_ON 4
#define TMPFILES_OFF 5
#define THUMBNAILS_ON 6
#define THUMBNAILS_OFF 7
#define SYSTMPFILES_ON 8
#define SYSTMPFILES_OFF 9
bool coreFiles = FALSE;
bool dirtyMark = FALSE;
bool winUpdateRefresh = FALSE;
void check(HWND hWnd);

LRESULT CALLBACK sysWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp)
		{
		case DESTROY_WINDOW_SYS:
			DestroyWindow(hWnd);
			break;
		case CLEAN_NOW:
			check(hWnd);
			break;
		case CLEAN_ALL_NOW:
			coreFiles = TRUE;
			dirtyMark = TRUE;
			winUpdateRefresh = TRUE;
			check(hWnd);
			break;
		case TMPFILES_ON:
			coreFiles = TRUE;
			break;
		case THUMBNAILS_ON:
			dirtyMark = TRUE;
			break;
		case SYSTMPFILES_ON:
			winUpdateRefresh = TRUE;
			break;
		case TMPFILES_OFF:
			coreFiles = FALSE;
			break;
		case THUMBNAILS_OFF:
			dirtyMark = FALSE;
			break;
		case SYSTMPFILES_OFF:
			winUpdateRefresh = FALSE;
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void regSysClass(HINSTANCE hInst) {
	WNDCLASSW wcsys = { 0 };

	wcsys.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcsys.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcsys.hInstance = hInst;
	wcsys.lpszClassName = L"sysWindowClass";
	wcsys.lpfnWndProc = cleanWindowProcedure;
	wcsys.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassW(&wcsys);
}

void displaySysWindow(HWND hWnd) {
	HWND hSysWnd = CreateWindowW(L"sysWindowClass", L"System Health", WS_VISIBLE, 650, 320, 500, 400, hWnd, NULL, NULL, NULL);
	setFont();
	HWND fontDlg = CreateWindowEx(NULL, "Button", "Cancel", WS_VISIBLE | WS_CHILD, 50, 275, 100, 50, hSysWnd, (HMENU)DESTROY_WINDOW_SYS, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	// TMP FILES
	fontDlg = CreateWindowEx(NULL, "Button", "On", WS_VISIBLE | WS_CHILD, 50, 25, 50, 50, hSysWnd, (HMENU)TMPFILES_ON, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Off", WS_VISIBLE | WS_CHILD, 100, 25, 50, 50, hSysWnd, (HMENU)TMPFILES_OFF, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "static", "Core Files Check", WS_VISIBLE | WS_CHILD, 175, 40, 95, 50, hSysWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	// THUMBNAILS
	fontDlg = CreateWindowEx(NULL, "Button", "On", WS_VISIBLE | WS_CHILD, 50, 100, 50, 50, hSysWnd, (HMENU)THUMBNAILS_ON, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Off", WS_VISIBLE | WS_CHILD, 100, 100, 50, 50, hSysWnd, (HMENU)THUMBNAILS_OFF, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "static", "Dirty Mark Check", WS_VISIBLE | WS_CHILD, 175, 115, 95, 50, hSysWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	// SYS TEMP FILES
	fontDlg = CreateWindowEx(NULL, "Button", "On", WS_VISIBLE | WS_CHILD, 50, 175, 50, 50, hSysWnd, (HMENU)SYSTMPFILES_ON, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Off", WS_VISIBLE | WS_CHILD, 100, 175, 50, 50, hSysWnd, (HMENU)SYSTMPFILES_OFF, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "static", "Windows Update Refresh", WS_VISIBLE | WS_CHILD, 175, 190, 150, 50, hSysWnd, NULL, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);



	fontDlg = CreateWindowEx(NULL, "Button", "Check", WS_VISIBLE | WS_CHILD, 275, 275, 75, 50, hSysWnd, (HMENU)CLEAN_NOW, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);

	fontDlg = CreateWindowEx(NULL, "Button", "Check All", WS_VISIBLE | WS_CHILD, 350, 275, 75, 50, hSysWnd, (HMENU)CLEAN_ALL_NOW, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void check(HWND hWnd) {
	if (coreFiles == TRUE) {
		return;
	}
	else if (dirtyMark == TRUE) {
		return;
	}
	else if (winUpdateRefresh == TRUE) {
		return;
	}
	else {
		MessageBoxW(hWnd, L"Please set one of the options to true.", L"Boostd", MB_OK | MB_ICONERROR);
	}
}


// #     #            
// #  #  #  #  ###### # 
// #  #  #  #  #      # 
// #  #  #  #  #####  # 
// #  #  #  #  #      # 
// #  #  #  #  #      # 
//  ## ##   #  #      # 

#define DESTROY_WINDOW_WIFI 1

LRESULT CALLBACK wifiWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp)
		{
		case DESTROY_WINDOW_WIFI:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void regWifiClass(HINSTANCE hInst) {
	WNDCLASSW wcw = { 0 };
	
	wcw.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcw.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcw.hInstance = hInst;
	wcw.lpszClassName = L"wifiWindowClass";
	wcw.lpfnWndProc = cleanWindowProcedure;
	wcw.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassW(&wcw);
}

void displayWifiWindow(HWND hWnd) {
	HWND hWifiWnd = CreateWindowW(L"wifiWindowClass", L"Wifi Clean", WS_VISIBLE, 650, 320, 500, 400, hWnd, NULL, NULL, NULL);
	setFont();
	HWND fontDlg = CreateWindowEx(NULL, "Button", "Cancel", WS_VISIBLE | WS_CHILD, 50, 275, 100, 50, hWifiWnd, (HMENU)DESTROY_WINDOW_WIFI, NULL, NULL);
	SendMessage(fontDlg, WM_SETFONT, (WPARAM)hFont, TRUE);
}