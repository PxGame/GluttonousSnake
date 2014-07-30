#include "Desktop.h"


CDesktop::CDesktop()
{
}


CDesktop::~CDesktop()
{
	//释放DC句柄
	ReleaseDC(m_hWnd, m_hDC);

	//释放动态申请的数组空间
	for (int i = 0; i < m_array_x; i++)
	{
		delete(m_desk[i]);
	}
	delete(m_desk);
}

void CDesktop::InitDesktop(HINSTANCE hInstance, HWND hWnd,CSnake* snake)
{
	m_hInst = hInstance;
	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);
	m_snake = snake;
	m_snake->InitSnake(2,2);

	GetClientRect(m_hWnd, &m_clientRt);//获取用户区大小
	m_width = m_clientRt.right - m_clientRt.left;//获取长宽
	m_height = m_clientRt.bottom - m_clientRt.top;

	//根据单元大小和用户区的大小动态设置数组大小	
	m_array_x = (m_clientRt.right - m_clientRt.left) / CELLSIZE;
	m_array_y = (m_clientRt.bottom - m_clientRt.top) / CELLSIZE;
	m_desk = new int*[m_array_x];//动态申请数组空间
	for (int i = 0; i < m_array_x; i++)
	{
		m_desk[i] = new int[m_array_y];
	}
}

void CDesktop::DrawDesktop(void)
{
	m_hBrush = CreateSolidBrush(BLACK_BRUSH);//初始化黑画刷
	SelectObject(m_hDC, m_hBrush);//选择画刷
	for (int i = 0; i < m_array_x; i++)//画竖线
	{
		MoveToEx(m_hDC, i*CELLSIZE, 0, NULL);
		LineTo(m_hDC, i*CELLSIZE, m_array_y*CELLSIZE);
	}
	for (int i = 0; i < m_array_y; i++)//画横线
	{
		MoveToEx(m_hDC, 0, i*CELLSIZE, NULL);
		LineTo(m_hDC, m_array_x*CELLSIZE, i*CELLSIZE);
	}
	DeleteObject(m_hBrush);//删除画刷
}

void CDesktop::DrawSnake(void)
{
	m_hBrush = CreateSolidBrush(BLACK_BRUSH);//初始化黑画刷
	RECT rt;
	SnakeNode* node = m_snake->m_front;//复制头指针
	while (node != NULL)
	{
		//设置结点矩形范围并画出矩形
		SetRect(&rt, node->pos_x * CELLSIZE, node->pos_y * CELLSIZE,
			node->pos_x * CELLSIZE + CELLSIZE, node->pos_y * CELLSIZE + CELLSIZE);
		FillRect(m_hDC, &rt, m_hBrush);

		//移到下一个结点
		node = node->next;
	}

	DeleteObject(m_hBrush);//删除画刷
}