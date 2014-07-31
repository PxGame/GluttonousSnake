# define _CRT_SECURE_NO_WARNINGS
# pragma once
# include <Windows.h>
# include <time.h>
# include "Snake.h"

extern int m_cellSize;//声明外部变量，在main.h文件中

enum DesktopStatus{
	nothing,
	snake,
	food
};

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
	BOOL DrawDesktop(void);
	void AddFood(void);

public :
};

