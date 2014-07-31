# define _CRT_SECURE_NO_WARNINGS
# pragma once
# include <Windows.h>
# include <time.h>
# include "Snake.h"

extern int m_cellSize;//�����ⲿ��������main.h�ļ���

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
	int **m_desk;//��̬�������̴�С
	int m_array_x;//�����±�
	int m_array_y;

protected:
	RECT m_clientRt;//�û������С
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

