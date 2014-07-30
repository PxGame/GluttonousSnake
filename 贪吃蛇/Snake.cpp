#include "Snake.h"


CSnake::CSnake()
{
}


CSnake::~CSnake()
{
}

void CSnake::InitSnake(int x, int y)
{
	m_front = new SnakeNode;//����ռ�
	m_back = new SnakeNode;
	
	m_front->dFlag = right;//���÷���״̬
	m_front->dFlag = right;

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
	switch (dFlag)//�����β�dFlag���þɵ�β����dFlag������,����Ϊ�෴�ķ��򣬷����򲻱�
	{
	case up:
	case leftUp:
	case rightUp:
		if (m_front->dFlag != down)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
			{
			case up:
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
			save->dFlag = up;			//�����µķ����־
			save->pos_x = m_front->pos_x;
			save->pos_y = m_front->pos_y + 1;//��������
		}
		break;
	case down:
	case leftDown:
	case rightDown:
		if (m_front->dFlag != up)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
			{
			case down:
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
			save->dFlag = down;			//�����µķ����־
			save->pos_x = m_front->pos_x;//��������
			save->pos_y = m_front->pos_y - 1;
		}
		break;
	case left: 
	case upLeft:
	case downLeft:
		if (m_front->dFlag != right)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
			{
			case up:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y + 1;
				break;
			case down:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y - 1;
				break;
			case left:
				save->pos_x = m_front->pos_x - 1;
				save->pos_y = m_front->pos_y;
				break;
			}
		}
		else
		{
			save->dFlag = left;			//�����µķ����־
			save->pos_x = m_front->pos_x - 1;//��������
			save->pos_y = m_front->pos_y;
		}
		break;
	case right:
	case upRight:
	case downRight:
		if (m_front->dFlag != left)
		{
			save->dFlag = dFlag;		//�����µķ����־
			switch (dFlag)				//�����µ�����
			{
			case up:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y + 1;
				break;
			case down:
				save->pos_x = m_front->pos_x;
				save->pos_y = m_front->pos_y - 1;
				break;
			case right:
				save->pos_x = m_front->pos_x + 1;
				save->pos_y = m_front->pos_y;
				break;
			}
		}
		else
		{
			save->dFlag = right;		//�����µķ����־
			save->pos_x = m_front->pos_x + 1;//��������
			save->pos_y = m_front->pos_y;
		}
		break;
	}
	m_front = save;//���ɵ�β�������Ϊ�µ�ͷ���
}