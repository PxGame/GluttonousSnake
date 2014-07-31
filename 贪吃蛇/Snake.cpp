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

	m_front = new SnakeNode;//����ռ�
	m_back = new SnakeNode;
	
	m_front->dFlag = dFlag;//���÷���״̬
	m_front->dFlag = dFlag;

	m_front->pos_x = x;//����λ��
	m_front->pos_y = y;
	m_back->pos_x = x - 1;
	m_back->pos_y = y;

	m_front->next = m_back;//���Ӻ�һ�����
	m_back->next = NULL;
	m_front->last = NULL;//����ǰһ�����
	m_back->last = m_front;
}

void CSnake::Move(DirectionFlag dFlag)
{
	m_back_last = *m_back;//�����ƶ�ǰ����Ϣ�����������

	SnakeNode* save;

	//��β����ƶ���ͷ���ǰ����Ϊ�µ�ͷ���
	save = m_back;						//���ݾɵ�β���
	//1.�Ƴ��ɵ�β���
	m_back = m_back->last;				//βָ��ǰ��һ�����
	m_back->next = NULL;				//�ÿ��µ�β������һ�����
	//2.���Ƴ��ɵ�β�������Ϊ�µ�ͷ���
	save->next = m_front;				//�ɵ�β���ָ��ɵ�ͷ���
	m_front->last = save;				//�ɵ�ͷ����ǰһ�����ָ���Ϊ�ɵ�β���
	save->last = NULL;					//�ɵ�β����ǰһ������ÿ�
	switch (m_front->dFlag)//�����β�dFlag���þɵ�β����dFlag������,����Ϊ�෴�ķ��򣬷����򲻱�
	{
	case up:
		if (dFlag != down)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
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
			save->dFlag = m_front->dFlag;//����ԭ��״̬
			save->pos_x = m_front->pos_x;
			save->pos_y = m_front->pos_y - 1;//��������
		}
		break;
	case down:
		if (dFlag != up)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
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
			save->dFlag = m_front->dFlag;//����ԭ��״̬
			save->pos_x = m_front->pos_x;//��������
			save->pos_y = m_front->pos_y + 1;
		}
		break;
	case left: 
		if (dFlag != right)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
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
			save->dFlag = m_front->dFlag;//����ԭ��״̬
			save->pos_x = m_front->pos_x - 1;//��������
			save->pos_y = m_front->pos_y;
		}
		break;
	case right:
		if (dFlag != left)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
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
			save->dFlag = m_front->dFlag;//����ԭ��״̬
			save->pos_x = m_front->pos_x + 1;//��������
			save->pos_y = m_front->pos_y;
		}
		break;
	}
	m_front = save;//���ɵ�β�������Ϊ�µ�ͷ���
	
}

void CSnake::Add(void)
{
	SnakeNode* new_back = new SnakeNode(m_back_last);
	new_back->last = m_back;//�����������
	m_back->next = new_back;
	new_back->next = NULL;

	m_back = new_back;//�½������Ϊβ���
}