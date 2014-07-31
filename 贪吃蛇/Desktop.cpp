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

	GetClientRect(m_hWnd, &m_clientRt);//获取用户区大小
	m_width = m_clientRt.right - m_clientRt.left;//获取长宽
	m_height = m_clientRt.bottom - m_clientRt.top;

	//根据单元大小和用户区的大小动态设置数组大小	
	m_array_x = (m_clientRt.right - m_clientRt.left) / m_cellSize;
	m_array_y = (m_clientRt.bottom - m_clientRt.top) / m_cellSize;
	m_desk = new int*[m_array_x];//动态申请数组空间
	for (int i = 0; i < m_array_x; i++)
	{
		m_desk[i] = new int[m_array_y];
	}
	for (int i = 0; i < m_array_x; i++)//初始化数组
	{
		for (int j = 0; j < m_array_y; j++)
		{
			m_desk[i][j] = nothing;
		}
	}

	m_snake->InitSnake(m_hWnd, m_array_x / 2, m_array_x / 2, left);
}

BOOL CDesktop::DrawDesktop(void)
{
	RECT rt_food, rt_snake;
	///////////////////////////////画网格///////////////////////////////////////////
	m_hBrush = CreateSolidBrush(BLACK_BRUSH);//初始化黑画刷
	SelectObject(m_hDC, m_hBrush);//选择画刷
	for (int i = 0; i < m_array_x; i++)//画竖线
	{
		MoveToEx(m_hDC, i*m_cellSize, 0, NULL);
		LineTo(m_hDC, i*m_cellSize, m_array_y*m_cellSize);
	}
	for (int i = 0; i < m_array_y; i++)//画横线
	{
		MoveToEx(m_hDC, 0, i*m_cellSize, NULL);
		LineTo(m_hDC, m_array_x*m_cellSize, i*m_cellSize);
	}


	///////////////////////////////////添加蛇//////////////////////////////////////////
	for (int i = 0; i < m_array_x; i++)//清除原有snake的状态
	{
		for (int j = 0; j < m_array_y; j++)
		{
			if (m_desk[i][j] == snake)
			{
				m_desk[i][j] = nothing;
			}
		}
	}
	SnakeNode* node = m_snake->m_front;//复制头指针

	if (node->pos_x < 0 || node->pos_x >= m_array_x ||
		node->pos_y < 0 || node->pos_y >= m_array_y)
	{
		KillTimer(m_hWnd, 0);
		KillTimer(m_hWnd, 1);
		MessageBox(m_hWnd, "撞墙而死。。\n游戏失败！单击退出游戏。", "游戏提示", MB_OK);
		return FALSE;
	}

	if (m_desk[node->pos_x][node->pos_y] == food)//判断是否吃到食物
	{
		m_snake->Add();//增加结点
	}

	while (node != NULL)
	{
		if (m_desk[node->pos_x][node->pos_y] == snake)//判断是否吃到自己
		{
			KillTimer(m_hWnd, 0);
			KillTimer(m_hWnd, 1);
			MessageBox(m_hWnd, "吃自己干嘛！\n游戏失败！单击退出游戏。", "游戏提示", MB_OK);
			return FALSE;
		}
		//设置m_desk新的状态
		m_desk[node->pos_x][node->pos_y] = snake;

		//移到下一个结点
		node = node->next;
	}
	////////////////////////////////绘图/////////////////////////////////////////////
	for (int i = 0; i < m_array_x; i++)
	{
		for (int j = 0; j < m_array_y; j++)
		{
			if (m_desk[i][j] == food)//画食物
			{
				m_hBrush = CreateSolidBrush(RGB(255, 0, 0));//初始化红画刷
				//设置结点矩形范围并画出矩形
				SetRect(&rt_food, i * m_cellSize, j * m_cellSize,
					i * m_cellSize + m_cellSize, j * m_cellSize + m_cellSize);
				FillRect(m_hDC, &rt_food, m_hBrush);
			}
			if (m_desk[i][j] == snake)//画蛇
			{
				m_hBrush = CreateSolidBrush(BLACK_BRUSH);//初始化黑画刷
				//设置结点矩形范围并画出矩形
				SetRect(&rt_snake, i * m_cellSize, j * m_cellSize,
					i * m_cellSize + m_cellSize, j * m_cellSize + m_cellSize);
				FillRect(m_hDC, &rt_snake, m_hBrush);
			}
		}
	}
	DeleteObject(m_hBrush);//删除画刷

	return TRUE;
}

void CDesktop::AddFood(void)
{
	int food_x = 0;
	int food_y = 0;
	srand((unsigned int)time(NULL));
	while (m_desk[food_x][food_y] != nothing)
	{
		food_x = rand() % m_array_x;
		food_y = rand() % m_array_y;
	}
	m_desk[food_x][food_y] = food;
}