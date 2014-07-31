#include "Snake.h"


CSnake::CSnake()
{
}


CSnake::~CSnake()
{
}

void CSnake::InitSnake(HWND hWnd, int x, int y, DirectionFlag dFlag)
{
	m_hWnd = hWnd;

	m_front = new SnakeNode;//申请空间
	m_back = new SnakeNode;
	
	m_front->dFlag = dFlag;//设置方向状态
	m_front->dFlag = dFlag;

	m_front->pos_x = x;//设置位置
	m_front->pos_y = y;
	m_back->pos_x = x - 1;
	m_back->pos_y = y;

	m_front->next = m_back;//连接后一个结点
	m_back->next = NULL;
	m_front->last = NULL;//连接前一个结点
	m_back->last = m_front;
}

void CSnake::Move(DirectionFlag dFlag)
{
	m_back_last = *m_back;//保存移动前的信息用于新增结点

	SnakeNode* save;

	//将尾结点移动到头结点前，成为新的头结点
	save = m_back;						//备份旧的尾结点
	//1.移除旧的尾结点
	m_back = m_back->last;				//尾指针前移一个结点
	m_back->next = NULL;				//置空新的尾结点的下一个结点
	//2.将移除旧的尾结点设置为新的头结点
	save->next = m_front;				//旧的尾结点指向旧的头结点
	m_front->last = save;				//旧的头结点的前一个结点指针的为旧的尾结点
	save->last = NULL;					//旧的尾结点的前一个结点置空
	switch (m_front->dFlag)//根据形参dFlag设置旧的尾结点的dFlag和坐标,不能为相反的方向，否则方向不变
	{
	case up:
		if (dFlag != down)
		{
			save->dFlag = dFlag;		//设置新的方向标志
			switch (dFlag)				//设置新的坐标
			{
			case up:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y - 1;
				break;
			case left:
				save->pos_x = m_front->pos_x - 1;
				save->pos_y = m_front->pos_y;
				break;
			case right:
				save->pos_x = m_front->pos_x + 1;
				save->pos_y = m_front->pos_y;
				break;
			}
		}
		else
		{
			save->dFlag = m_front->dFlag;//保持原有状态
			save->pos_x = m_front->pos_x;
			save->pos_y = m_front->pos_y - 1;//继续向上
		}
		break;
	case down:
		if (dFlag != up)
		{
			save->dFlag = dFlag;		//设置新的方向标志
			switch (dFlag)				//设置新的坐标
			{
			case down:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y + 1;
				break;
			case left:
				save->pos_x = m_front->pos_x - 1;
				save->pos_y = m_front->pos_y;
				break;
			case right:
				save->pos_x = m_front->pos_x + 1;
				save->pos_y = m_front->pos_y;
				break;
			}
		}
		else
		{
			save->dFlag = m_front->dFlag;//保持原有状态
			save->pos_x = m_front->pos_x;//继续向下
			save->pos_y = m_front->pos_y + 1;
		}
		break;
	case left: 
		if (dFlag != right)
		{
			save->dFlag = dFlag;		//设置新的方向标志
			switch (dFlag)				//设置新的坐标
			{
			case up:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y - 1;
				break;
			case down:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y + 1;
				break;
			case left:
				save->pos_x = m_front->pos_x - 1;
				save->pos_y = m_front->pos_y;
				break;
			}
		}
		else
		{
			save->dFlag = m_front->dFlag;//保持原有状态
			save->pos_x = m_front->pos_x - 1;//继续向左
			save->pos_y = m_front->pos_y;
		}
		break;
	case right:
		if (dFlag != left)
		{
			save->dFlag = dFlag;		//设置新的方向标志
			switch (dFlag)				//设置新的坐标
			{
			case up:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y - 1;
				break;
			case down:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y + 1;
				break;
			case right:
				save->pos_x = m_front->pos_x + 1;
				save->pos_y = m_front->pos_y;
				break;
			}
		}
		else
		{
			save->dFlag = m_front->dFlag;//保持原有状态
			save->pos_x = m_front->pos_x + 1;//继续向右
			save->pos_y = m_front->pos_y;
		}
		break;
	}
	m_front = save;//将旧的尾结点设置为新的头结点
	
}

void CSnake::Add(void)
{
	SnakeNode* new_back = new SnakeNode(m_back_last);
	new_back->last = m_back;//连接新增结点
	m_back->next = new_back;
	new_back->next = NULL;

	m_back = new_back;//新结点设置为尾结点
}