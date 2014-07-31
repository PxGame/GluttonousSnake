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
	struct Node* last;//��һ�����
	struct Node* next;//��һ�����
}SnakeNode;//�߽��

class CSnake
{
protected :
	HWND m_hWnd;
public :
	SnakeNode* m_front;//ͷָ��
	SnakeNode* m_back;//βָ��
	SnakeNode m_back_last;//������β����ǰ����Ϣ
public:
	CSnake();
	~CSnake();

public :
	void InitSnake(HWND hWnd, int x, int y, DirectionFlag dFlag);//��ʼ����
	void Move(DirectionFlag dFlag);//�ƶ���
	void Add(void);//���һ�����
};

