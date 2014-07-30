# define _CRT_SECURE_NO_WARNINGS
# pragma once
# include <Windows.h>
# include "Snake.h"

# define  CELLSIZE 20//20*20���صķ��񣬱��뱻main.cpp�е�CLIENT_WITDH��CLIENT_HEIGHT����

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
	void DrawDesktop(void);
	void DrawSnake(void);
};

