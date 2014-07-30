# define _CRT_SECURE_NO_WARNINGS
# include <Windows.h>
# include <iostream>

# include "Desktop.h"
# include "Snake.h"

# define CLIENT_WITDH 600	//必需是Desktop.h中CELLSIZE的整数倍
# define CLIENT_HEIGHT 600	//

//全局变量
HINSTANCE m_hInst = NULL;
HWND m_hWnd = NULL;
LPCSTR m_className = "WinClassName";

int m_sWidth = GetSystemMetrics(SM_CXSCREEN);//获取屏幕参数
int m_sHeight = GetSystemMetrics(SM_CYSCREEN);
RECT m_clientRt;//设置用户区大小

CDesktop m_desktop;//桌面类
CSnake m_snake;//蛇类

//函数声明
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//主消息响应
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT nIDEvent, DWORD dwTime);//计时器响应
BOOL InitApplication(HINSTANCE hInstance);//初始化程序

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	m_hInst = hInstance;//备份
	SetRect(&m_clientRt, 0, 0, CLIENT_WITDH, CLIENT_HEIGHT);//设置用户区RECT大小

	if (!InitApplication(m_hInst))
	{
		return ERROR;
	}
	m_desktop.InitDesktop(m_hInst, m_hWnd, &m_snake);//初始化界面类
	ShowWindow(m_hWnd, SW_SHOW);

	SetTimer(m_hWnd, 0, 2000, TimerProc);//计时器

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WinProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE :
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_PAINT :
		m_desktop.DrawDesktop();
		m_desktop.DrawSnake();
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_CLOSE :
		if (IDYES == MessageBox(m_hWnd, "是否关闭游戏？", "提示", NULL))
		{
			DestroyWindow(m_hWnd);
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_DESTROY :
		PostQuitMessage(0);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	default :
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
void CALLBACK TimerProc(HWND hWnd,
	UINT uMsg,
	UINT nIDEvent,
	DWORD dwTime)
{
	switch (nIDEvent)
	{
	case 0:
		InvalidateRect(m_hWnd, NULL, TRUE);
		UpdateWindow(m_hWnd);
		m_snake.Move(up);
		SendMessage(m_hWnd, WM_PAINT, 0, 0);
		break;
	}

}

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WinProc;
	wnd.lpszClassName = m_className;
	wnd.lpszMenuName = NULL;
	wnd.style = NULL;

	if (!RegisterClass(&wnd))
	{
		MessageBox(NULL, "RegisterClass(&wnd) 失败！", "错误", NULL);
	}

	//按用户区来设置窗口
	int wndWidth = 0;
	int wndHeight = 0;
	AdjustWindowRect(&m_clientRt, WS_CAPTION | WS_SYSMENU, FALSE);//调整为窗口大小
	wndWidth = m_clientRt.right - m_clientRt.left;//计算大小
	wndHeight = m_clientRt.bottom - m_clientRt.top;
	//创建窗口
	m_hWnd = CreateWindow(m_className, "贪吃蛇", WS_CAPTION | WS_SYSMENU,
		(m_sWidth - wndWidth) / 2, (m_sHeight - wndHeight) / 2, wndWidth, wndHeight, 
		NULL, NULL, hInstance, NULL);

	if (m_hWnd == NULL)//判断主窗口是否创建成功
	{
		char str[200];
		sprintf(str, "错误代码：%d\nBOOL InitApplication(HINSTANCE hInstance) 中 CreateWindow 失败！\nwndWidth = %d\nwndHeight = %d", GetLastError(), wndWidth ,wndHeight);
		MessageBox(NULL, str, "错误", NULL);
		return FALSE;
	}

	return TRUE;
}