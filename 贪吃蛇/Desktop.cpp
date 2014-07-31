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

	GetClientRect(m_hWnd, &m_clientRt);//��ȡ�û�����С
	m_width = m_clientRt.right - m_clientRt.left;//��ȡ����
	m_height = m_clientRt.bottom - m_clientRt.top;

	//���ݵ�Ԫ��С���û����Ĵ�С��̬���������С	
	m_array_x = (m_clientRt.right - m_clientRt.left) / m_cellSize;
	m_array_y = (m_clientRt.bottom - m_clientRt.top) / m_cellSize;
	m_desk = new int*[m_array_x];//��̬��������ռ�
	for (int i = 0; i < m_array_x; i++)
	{
		m_desk[i] = new int[m_array_y];
	}
	for (int i = 0; i < m_array_x; i++)//��ʼ������
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
	///////////////////////////////������///////////////////////////////////////////
	m_hBrush = CreateSolidBrush(BLACK_BRUSH);//��ʼ���ڻ�ˢ
	SelectObject(m_hDC, m_hBrush);//ѡ��ˢ
	for (int i = 0; i < m_array_x; i++)//������
	{
		MoveToEx(m_hDC, i*m_cellSize, 0, NULL);
		LineTo(m_hDC, i*m_cellSize, m_array_y*m_cellSize);
	}
	for (int i = 0; i < m_array_y; i++)//������
	{
		MoveToEx(m_hDC, 0, i*m_cellSize, NULL);
		LineTo(m_hDC, m_array_x*m_cellSize, i*m_cellSize);
	}


	///////////////////////////////////�����//////////////////////////////////////////
	for (int i = 0; i < m_array_x; i++)//���ԭ��snake��״̬
	{
		for (int j = 0; j < m_array_y; j++)
		{
			if (m_desk[i][j] == snake)
			{
				m_desk[i][j] = nothing;
			}
		}
	}
	SnakeNode* node = m_snake->m_front;//����ͷָ��

	if (node->pos_x < 0 || node->pos_x >= m_array_x ||
		node->pos_y < 0 || node->pos_y >= m_array_y)
	{
		KillTimer(m_hWnd, 0);
		KillTimer(m_hWnd, 1);
		MessageBox(m_hWnd, "ײǽ��������\n��Ϸʧ�ܣ������˳���Ϸ��", "��Ϸ��ʾ", MB_OK);
		return FALSE;
	}

	if (m_desk[node->pos_x][node->pos_y] == food)//�ж��Ƿ�Ե�ʳ��
	{
		m_snake->Add();//���ӽ��
	}

	while (node != NULL)
	{
		if (m_desk[node->pos_x][node->pos_y] == snake)//�ж��Ƿ�Ե��Լ�
		{
			KillTimer(m_hWnd, 0);
			KillTimer(m_hWnd, 1);
			MessageBox(m_hWnd, "���Լ����\n��Ϸʧ�ܣ������˳���Ϸ��", "��Ϸ��ʾ", MB_OK);
			return FALSE;
		}
		//����m_desk�µ�״̬
		m_desk[node->pos_x][node->pos_y] = snake;

		//�Ƶ���һ�����
		node = node->next;
	}
	////////////////////////////////��ͼ/////////////////////////////////////////////
	for (int i = 0; i < m_array_x; i++)
	{
		for (int j = 0; j < m_array_y; j++)
		{
			if (m_desk[i][j] == food)//��ʳ��
			{
				m_hBrush = CreateSolidBrush(RGB(255, 0, 0));//��ʼ���컭ˢ
				//���ý����η�Χ����������
				SetRect(&rt_food, i * m_cellSize, j * m_cellSize,
					i * m_cellSize + m_cellSize, j * m_cellSize + m_cellSize);
				FillRect(m_hDC, &rt_food, m_hBrush);
			}
			if (m_desk[i][j] == snake)//����
			{
				m_hBrush = CreateSolidBrush(BLACK_BRUSH);//��ʼ���ڻ�ˢ
				//���ý����η�Χ����������
				SetRect(&rt_snake, i * m_cellSize, j * m_cellSize,
					i * m_cellSize + m_cellSize, j * m_cellSize + m_cellSize);
				FillRect(m_hDC, &rt_snake, m_hBrush);
			}
		}
	}
	DeleteObject(m_hBrush);//ɾ����ˢ

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