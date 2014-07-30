# define _CRT_SECURE_NO_WARNINGS
# pragma once
# include <Windows.h>
# include <iostream>

enum DirectionFlag{
	up, upLeft, upRight,
	down, downLeft, downRight,
	left, leftUp, leftDown,
	right, rightUp, rightDown
};//�����ʶö��

typedef struct Node{
	DirectionFlag dFlag;
	int pos_x;//��ǰ����
	int pos_y;
	struct Node* next;//��һ�����
	struct Node* last;//��һ�����
}SnakeNode;//�߽��

class CSnake
{
public :
	SnakeNode* m_front;//ͷָ��
	SnakeNode* m_back;//βָ��

public:
	CSnake();
	~CSnake();

public :
	void InitSnake(int x,int y);//��ʼ����
	void Move(DirectionFlag dFlag);//�ƶ���
};

