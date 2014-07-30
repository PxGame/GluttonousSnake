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
	struct Node* next;//下一个结点
	struct Node* last;//上一个结点
}SnakeNode;//蛇结点

class CSnake
{
public :
	SnakeNode* m_front;//头指针
	SnakeNode* m_back;//尾指针

public:
	CSnake();
	~CSnake();

public :
	void InitSnake(int x,int y);//初始化蛇
	void Move(DirectionFlag dFlag);//移动蛇
};

