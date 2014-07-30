#include "Desktop.h"


CDesktop::CDesktop()
{
}


CDesktop::~CDesktop()
{
	//�ͷ�DC���
	ReleaseDC(m_hWnd, m_hDC);

	//�ͷŶ�̬���������ռ�
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

	GetClientRect(m_hWnd, &m_clientRt);//��ȡ�û�����С
	m_width = m_clientRt.right - m_clientRt.left;//��ȡ����
	m_height = m_clientRt.bottom - m_clientRt.top;

	//���ݵ�Ԫ��С���û����Ĵ�С��̬���������С	
	m_array_x = (m_clientRt.right - m_clientRt.left) / CELLSIZE;
	m_array_y = (m_clientRt.bottom - m_clientRt.top) / CELLSIZE;
	m_desk = new int*[m_array_x];//��̬��������ռ�
	for (int i = 0; i < m_array_x; i++)
	{
		m_desk[i] = new int[m_array_y];
	}
}

void CDesktop::DrawDesktop(void)
{
	m_hBrush = CreateSolidBrush(BLACK_BRUSH);//��ʼ���ڻ�ˢ
	SelectObject(m_hDC, m_hBrush);//ѡ��ˢ
	for (int i = 0; i < m_array_x; i++)//������
	{
		MoveToEx(m_hDC, i*CELLSIZE, 0, NULL);
		LineTo(m_hDC, i*CELLSIZE, m_array_y*CELLSIZE);
	}
	for (int i = 0; i < m_array_y; i++)//������
	{
		MoveToEx(m_hDC, 0, i*CELLSIZE, NULL);
		LineTo(m_hDC, m_array_x*CELLSIZE, i*CELLSIZE);
	}
	DeleteObject(m_hBrush);//ɾ����ˢ
}

void CDesktop::DrawSnake(void)
{
	m_hBrush = CreateSolidBrush(BLACK_BRUSH);//��ʼ���ڻ�ˢ
	RECT rt;
	SnakeNode* node = m_snake->m_front;//����ͷָ��
	while (node != NULL)
	{
		//���ý����η�Χ����������
		SetRect(&rt, node->pos_x * CELLSIZE, node->pos_y * CELLSIZE,
			node->pos_x * CELLSIZE + CELLSIZE, node->pos_y * CELLSIZE + CELLSIZE);
		FillRect(m_hDC, &rt, m_hBrush);

		//�Ƶ���һ�����
		node = node->next;
	}

	DeleteObject(m_hBrush);//ɾ����ˢ
}