# define _CRT_SECURE_NO_WARNINGS
# pragma once
# include <Windows.h>
# include "Snake.h"

# define  CELLSIZE 20//20*20像素的方格，必须被main.cpp中的CLIENT_WITDH和CLIENT_HEIGHT整除

class CDesktop
{
protected:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	HBRUSH m_hBrush;

protected :
	CSnake* m_snake;

protected:
	int **m_desk;//动态设置棋盘大小
	int m_array_x;//数组下标
	int m_array_y;

protected:
	RECT m_clientRt;//用户区域大小
	int m_width;
	int m_height;


public:
	CDesktop();
	~CDesktop();

public :
	void InitDesktop(HINSTANCE hInstance, HWND hWnd, CSnake* snake);
	void DrawDesktop(void);
	void DrawSnake(void);
};

