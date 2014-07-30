# define _CRT_SECURE_NO_WARNINGS
# include <Windows.h>
# include <iostream>

# include "Desktop.h"
# include "Snake.h"

# define CLIENT_WITDH 600	//������Desktop.h��CELLSIZE��������
# define CLIENT_HEIGHT 600	//

//ȫ�ֱ���
HINSTANCE m_hInst = NULL;
HWND m_hWnd = NULL;
LPCSTR m_className = "WinClassName";

int m_sWidth = GetSystemMetrics(SM_CXSCREEN);//��ȡ��Ļ����
int m_sHeight = GetSystemMetrics(SM_CYSCREEN);
RECT m_clientRt;//�����û�����С

CDesktop m_desktop;//������
CSnake m_snake;//����

//��������
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//����Ϣ��Ӧ
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT nIDEvent, DWORD dwTime);//��ʱ����Ӧ
BOOL InitApplication(HINSTANCE hInstance);//��ʼ������

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	m_hInst = hInstance;//����
	SetRect(&m_clientRt, 0, 0, CLIENT_WITDH, CLIENT_HEIGHT);//�����û���RECT��С

	if (!InitApplication(m_hInst))
	{
		return ERROR;
	}
	m_desktop.InitDesktop(m_hInst, m_hWnd, &m_snake);//��ʼ��������
	ShowWindow(m_hWnd, SW_SHOW);

	SetTimer(m_hWnd, 0, 2000, TimerProc);//��ʱ��

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
		if (IDYES == MessageBox(m_hWnd, "�Ƿ�ر���Ϸ��", "��ʾ", NULL))
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
		MessageBox(NULL, "RegisterClass(&wnd) ʧ�ܣ�", "����", NULL);
	}

	//���û��������ô���
	int wndWidth = 0;
	int wndHeight = 0;
	AdjustWindowRect(&m_clientRt, WS_CAPTION | WS_SYSMENU, FALSE);//����Ϊ���ڴ�С
	wndWidth = m_clientRt.right - m_clientRt.left;//�����С
	wndHeight = m_clientRt.bottom - m_clientRt.top;
	//��������
	m_hWnd = CreateWindow(m_className, "̰����", WS_CAPTION | WS_SYSMENU,
		(m_sWidth - wndWidth) / 2, (m_sHeight - wndHeight) / 2, wndWidth, wndHeight, 
		NULL, NULL, hInstance, NULL);

	if (m_hWnd == NULL)//�ж��������Ƿ񴴽��ɹ�
	{
		char str[200];
		sprintf(str, "������룺%d\nBOOL InitApplication(HINSTANCE hInstance) �� CreateWindow ʧ�ܣ�\nwndWidth = %d\nwndHeight = %d", GetLastError(), wndWidth ,wndHeight);
		MessageBox(NULL, str, "����", NULL);
		return FALSE;
	}

	return TRUE;
}