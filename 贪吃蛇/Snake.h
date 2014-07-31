# define _CRT_SECURE_NO_WARNINGS
# pragma once
# include <Windows.h>
# include <iostream>

enum DirectionFlag{
	up, upLeft, upRight,
	down, downLeft, downRight,
	left, leftUp, leftDown,
	right, rightUp, rightDown
};//方向标识枚举

typedef struct Node{
	DirectionFlag dFlag;
	int pos_x;//当前坐标
	int pos_y;
	struct Node* last;//上一个结点
	struct Node* next;//下一个结点
}SnakeNode;//蛇结点

class CSnake
{
protected :
	HWND m_hWnd;
public :
	SnakeNode* m_front;//头指针
	SnakeNode* m_back;//尾指针
	SnakeNode m_back_last;//保存蛇尾更新前的信息
public:
	CSnake();
	~CSnake();

public :
	void InitSnake(HWND hWnd, int x, int y, DirectionFlag dFlag);//初始化蛇
	void Move(DirectionFlag dFlag);//移动蛇
	void Add(void);//添加一个结点
};

