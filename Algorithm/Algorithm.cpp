#include "Standard.h"

AIgorithm::AIgorithm()
{

}

AIgorithm::~AIgorithm()
{

}

void AIgorithm::Destroy()
{
	if (open_node != NULL)
	{
		delete open_node;
		while (open_node->Next != NULL)
		{
			delete open_node->Next;
			open_node->Next = open_node->Next->Next;
		}
	}
	if (close_node != NULL)
	{
		if (close_node->Next != NULL)
		{
			delete close_node->Next;
			close_node->Next = close_node->Next->Next;
		}
	}

	delete R;
	delete R_head;
	delete Stack_End;
	delete Stack_Head;
}

BOOL AIgorithm::Start(POINT start, POINT des)
{
	count = 0;

	ClearRep();
	ClearDIR();
	if (CheckNear(start, des, 0)) return TRUE;  //�켱 START�� DES�� ������ �ִ��� �Ǻ�
	if (CheckNaver(start)) return FALSE;       //start ���� 4ĭ�� ������� ������ ������ ����
	if (CheckNaver(des)) return FALSE;         //DESTINATION ���� 4ĭ�� ������� ������ ������ ���� 

	int i = SetDirection(start, des);         // ���������� �������� �������� �� ��������ΰ��� �˻� 
	SetStart(start);                          // ���� �˻��� �켱 �˻� ������ ���� 
	if (SearchStart(start, des)) return TRUE;  // �˻��� ������ 

	return FALSE;
}

BOOL AIgorithm::SearchStart(POINT start, POINT des) // �켱������ ���� ���������� 4���⿡ ���۳�带 ���� 
{
	int i = 4, j = 0;
	POINT b_start;
	while (j < 4)
	{
		if (CheckBox(start, direction[j]) == true)
		{
			b_start = start;
			switch (direction[j])
			{
				case 0:
					b_start.y = start.y + 1;
					break;

				case 1:
					b_start.y = start.y - 1;
					break;

				case 2:
					b_start.x = start.x - 1;
					break;

				case 3:
					b_start.x = start.x + 1;
					break;
			}

			if (m_Board.GetBlockInfo(b_start.x, b_start.y) == -1)
			{
				now_dir = j;
				if (Root(buf, des, direction[j])) return TRUE;
			}
		}
		
		j++;
	}

	return FALSE;
}

void AIgorithm::ClearDIR() //  ���⼳�� ���� �ʱ�ȭ 
{
	for (int i = 0; i < 4; i++)
		start_dir[i] = -1;
}

BOOL AIgorithm::Root(POINT next, POINT des, int dir) // ���� ���� ù��带 ���� �Լ� 
{
	R_head = new Road;
	R_head->p = next;
	R_head->turncount = 0;
	R_head->degree = 1;
	R_head->Next = NULL;
	R_head->Prev = NULL;
	R_head->value = 0;
	R_head->prev_dir = dir;

	if (CheckNear(next, des, 0)) // �������ִ��� �˻� 
	{
		SetLine(R_head->degree);

		DrawLine(MakePoint(next.x, next.y), dir, GetDirection(next, des));
		return TRUE;
	}

	//	if(CheckDirection(next, des, R->turncount)) AddCloseNode(R_head);

	POINT b_next;

	for (int i = 0; i < 4; i++) // ���� �켱������ ���� ���� �˻��� ������ �����Ͽ� �˻� 
	{
		b_next = next;
		switch (dir)
		{
			case 0:
				b_next.y = next.y + 1;
				break;

			case 1:
				b_next.y = next.y - 1;
				break;

			case 2:
				b_next.x = next.x - 1;
				break;

			case 3:
				b_next.x = next.x + 1;
				break;
		}

		if (CheckBox(next, direction[i]) == TRUE && Check4Dir(b_next.x, b_next.y) == TRUE)
		{
			if (RootSearch(R_head->direct[direction[i]], R_head, MakePoint(b_next.x, b_next.y), des, R_head->prev_dir, direction[i], R_head->turncount))
			{
				DrawLine(MakePoint(next.x, next.y), dir, direction[i]);
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL AIgorithm::RootSearch(Road* dir_R, Road* R_prev, POINT now, POINT des, int prev_dir, int dir, int count)
{// Root()�Լ����� ������� ��带 ������ �Լ� >> Road *dir_R : ������� ���� �ּ�  Road *R_prev : ������� �ּ� 
 //	POINT now : ���� ��ǥ POINT des : ������ �ּ�  int prev_dir ��������� ��������  int dir ��������  int count : ������ Ƚ�� 
	R = new Road;

	R->degree = R_prev->degree;
	R->degree++;
	R->Next = NULL;
	R->Prev = R_prev;
	dir_R = R;
	R->turncount = count;
	R->prev_dir = dir;
	R->p = now;
	R->value = 0;
	if (prev_dir != dir) R->turncount++;
	dir_R = R;
	if (R->turncount >= 3) return FALSE; // ������ 3ȸ �̻��̵Ǹ� FALSE ���� 
	//if (CheckCloseNode(R)) return FALSE; // ���� ����� ��尡 ��Ŭ���� ��忡 ��ϵǾ������� FALSE ���� 

	if (CheckNear(now, des, R->turncount))
	{
		SetLine(R->degree);
		DrawLine(MakePoint(now.x, now.y), dir, GetDirection(now, des));
		return TRUE; //�����ϸ� TURE ���� 
	}

	if (CheckDirection(now, des, R->prev_dir, R->turncount)) // ���� ��ǥ�� ������ ��ǥ�� ���ؼ� ������������ ������ �˻� 
	{
		AddCloseNode(R);
		return FALSE;
	}

	POINT b_now;

	if (CheckBox(now, dir))
	{
		b_now = now;
		switch (dir)
		{
			case 0:
				b_now.y = now.y + 1;
				break;

			case 1:
				b_now.y = now.y - 1;
				break;

			case 2:
				b_now.x = now.x - 1;
				break;

			case 3:
				b_now.x = now.x + 1;
				break;
		}

		if (Check4Dir(b_now.x, b_now.y) == TRUE)
		{
			if (RootSearch(R->direct[dir], R, MakePoint(b_now.x, b_now.y), des, R->prev_dir, dir, R->turncount))
			{
				DrawLine(MakePoint(now.x, now.y), dir, dir);
				return TRUE;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (direction[i] == dir)
			continue;

		b_now = now;

		switch (direction[i])
		{
			case 0:
				b_now.y = now.y + 1;
				break;

			case 1:
				b_now.y = now.y - 1;
				break;

			case 2:
				b_now.x = now.x - 1;
				break;

			case 3:
				b_now.x = now.x + 1;
				break;
		}

		if (CheckBox(now, direction[i]) == TRUE && Check4Dir(b_now.x, b_now.y) == TRUE)
		{
			if (RootSearch(R->direct[direction[i]], R, MakePoint(b_now.x, b_now.y), des, R->prev_dir, direction[i], R->turncount))
			{
				DrawLine(MakePoint(now.x, now.y), dir, direction[i]);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL AIgorithm::CheckDirection(POINT now, POINT des, int dir, int count) //���� ����� �������⿡ ��ġ�ϸ� ī���͸� ���� �ʴ´� ! �Ұ�!! 
{
	/*if(now.x - des.x != 0 ) count++;
	if(now.y - des.y != 0 ) count++;
	if(count > 3) return TRUE;         //count�� 3�̻��̸� TRUE ����*/
	if (dir == 0)
	{
		if (now.y - des.y > 0) count++;
		if (now.x - des.x != 0) count++;
	}
	else if (dir == 1)
	{
		if (now.y - des.y < 0) count++;
		if (now.x - des.x != 0) count++;
	}
	else if (dir == 2)
	{
		if (now.x - des.x < 0) count++;
		if (now.y - des.y != 0) count++;
	}
	else if (dir == 3)
	{
		if (now.x - des.x > 0) count++;
		if (now.y - des.y != 0) count++;
	}

	if (count > 2) return TRUE;
	return FALSE;
}

BOOL AIgorithm::Check4Dir(int x, int y)
{
	if (m_Board.Block[x][y] == -1) return TRUE;
	return FALSE;
}

void AIgorithm::AddOpenNode(Road* R_node)
{
	if (head_open_node->node == NULL)
	{
		head_open_node->node = R_node;
		end_open_node = head_open_node;
	}
	else
	{
		open_node = new set_nodes;
		open_node->node = R_node;
		end_open_node->Next = open_node;
		end_open_node = open_node;
	}
}

void AIgorithm::AddCloseNode(Road* R_node)
{
	if (head_close_node->node == NULL)
	{
		head_close_node->node = R_node;
		end_close_node = head_close_node;
	}
	else
	{
		set_nodes* close_node = new set_nodes;
		close_node->node = R_node;
		close_node->Next = NULL;
		end_close_node->Next = close_node;
		end_close_node = close_node;
	}
	count++;
}

BOOL AIgorithm::CheckOpenNode(Road* R_node)
{
	set_nodes* temp = new set_nodes;

	temp->node = head_open_node->node;

	while (temp->Next != NULL)
	{
		if (temp->node->degree == R_node->degree
			&& temp->node->p.x == R_node->p.x && temp->node->p.y == R_node->p.y
			&& temp->node->turncount == R_node->turncount
			&& temp->node->value == R_node->value) return TRUE;

		temp = temp->Next;
	}

	return FALSE;
}

BOOL AIgorithm::CheckCloseNode(Road* R_node)
{
	set_nodes* temp = new set_nodes;

	temp = head_close_node;

	return FALSE;
}

void AIgorithm::RemoveOpenNode(Road* R_node)
{

}

void AIgorithm::SetStart(POINT start) // START���� ���� ���ư� ������ ����
{
	int a = 0;
	int set[4] = { 0 };
	for (int i = 0; i < 2; i++)
	{
		if (start_dir[i] == 0)
		{
			direction[a] = 0; set[0] = 1; a++;
		}
		if (start_dir[i] == 1)
		{
			direction[a] = 1; set[1] = 1; a++;
		}
		if (start_dir[i] == 2)
		{
			direction[a] = 2; set[2] = 1; a++;
		}
		if (start_dir[i] == 3)
		{
			direction[a] = 3; set[3] = 1; a++;
		}
	}
	for (int i = 0; i < 4; i++)
		if (set[i] == 0)
		{
			direction[a] = i;
			a++;
		}
}

int AIgorithm::SetDirection(POINT start, POINT des) // START������ DES ���� �˻�
{
	int i = 0;
	if (start.y < des.y)
	{
		start_dir[i] = 0;
		i++;
	}
	if (start.y > des.y)
	{
		start_dir[i] = 1;
		i++;
	}
	if (start.y == des.y)
	{

	}
	if (start.x > des.x)
	{
		start_dir[i] = 2;
		i++;
	}
	if (start.x < des.x)
	{
		start_dir[i] = 3;
		i++;
	}
	return i;
}

BOOL AIgorithm::CheckNaver(POINT p)
{
	if (CheckBox(p, 0) && m_Board.GetBlockInfo(p.x, p.y + 1) == -1) return FALSE;
	if (CheckBox(p, 1) && m_Board.GetBlockInfo(p.x, p.y - 1) == -1) return FALSE;
	if (CheckBox(p, 2) && m_Board.GetBlockInfo(p.x - 1, p.y) == -1) return FALSE;
	if (CheckBox(p, 3) && m_Board.GetBlockInfo(p.x + 1, p.y) == -1) return FALSE;

	return TRUE;
}

BOOL AIgorithm::CheckNear(POINT now, POINT des, int count)
{
	if (count < 3)
	{
		if (CheckBox(now, 0) && now.x == des.x && now.y + 1 == des.y)
			if (m_Board.GetBlockInfo(now.x, now.y + 1) == m_Board.GetBlockInfo(des.x, des.y)) return 1;
			else return 0;

		if (CheckBox(now, 1) && now.x == des.x && now.y - 1 == des.y)
			if (m_Board.GetBlockInfo(now.x, now.y - 1) == m_Board.GetBlockInfo(des.x, des.y)) return 1;
			else return 0;

		if (CheckBox(now, 2) && now.x - 1 == des.x && now.y == des.y)
			if (m_Board.GetBlockInfo(now.x - 1, now.y) == m_Board.GetBlockInfo(des.x, des.y)) return 1;
			else return 0;

		if (CheckBox(now, 3) && now.x + 1 == des.x && now.y == des.y)
			if (m_Board.GetBlockInfo(now.x + 1, now.y) == m_Board.GetBlockInfo(des.x, des.y)) return 1;
			else return 0;
	}

	return 0;
}

BOOL AIgorithm::CheckBox(POINT p, int dir)
{
	switch (dir)
	{
	case 0:
		if (p.y < 9) return TRUE;
		break;

	case 1:
		if (p.y > 0) return TRUE;
		break;

	case 2:
		if (p.x > 0) return TRUE;
		break;

	case 3:
		if (p.x < 19) return TRUE;
		break;
	}
	return FALSE;
}

POINT AIgorithm::MakePoint(int x, int y)
{
	POINT p;
	p.x = x;
	p.y = y;
	return p;
}

void AIgorithm::AddStack(POINT p)
{
	if (Stack_Head == NULL)
	{
		Stack_Head->p = p;
		Stack_End = Stack_Head;
	}
	else
	{
		stacks* Stack = new stacks;
		Stack->p = p;
		Stack->Next = NULL;
		Stack_End->Next = Stack;
		Stack_End = Stack->Next;
	}
}

void AIgorithm::DrawLine(POINT p, int dir, int prev_dir)
{
	/*if (prev_dir == dir)
	{
		if (dir == 0 || dir == 1) m_Sprite->AddLine(p, 0);
		if (dir == 2 || dir == 3) m_Sprite->AddLine(p, 5);
	}
	else
	{
		if (dir == 0)
		{
			if (prev_dir == 2) m_Sprite->AddLine(p, 10);
			if (prev_dir == 3) m_Sprite->AddLine(p, 15);
		}
		if (dir == 1)
		{
			if (prev_dir == 2) m_Sprite->AddLine(p, 25);
			if (prev_dir == 3) m_Sprite->AddLine(p, 20);
		}
		if (dir == 2)
		{
			if (prev_dir == 0) m_Sprite->AddLine(p, 20);
			if (prev_dir == 1) m_Sprite->AddLine(p, 15);
		}
		if (dir == 3)
		{
			if (prev_dir == 0) m_Sprite->AddLine(p, 25);
			if (prev_dir == 1) m_Sprite->AddLine(p, 10);
		}
	}*/
}

int AIgorithm::GetDirection(POINT now, POINT des)
{
	if (now.x == des.x && now.y + 1 == des.y) return 0;
	if (now.x == des.x && now.y - 1 == des.y) return 1;
	if (now.x - 1 == des.x && now.y == des.y) return 2;
	if (now.x + 1 == des.x && now.y == des.y) return 3;
}

void AIgorithm::SetLine(int deg)
{
	//m_Sprite->InitLine(deg);
}

void AIgorithm::ClearRep()
{
	head_open_node = new set_nodes;
	head_close_node = new set_nodes;
	end_open_node = new set_nodes;
	end_close_node = new set_nodes;
	//Stack = new stacks;
	Stack_Head = new stacks;
	Stack_End = new stacks;

	//Stack->Next = NULL;
	//Stack_Head->p = MakePoint(0,0);

	Stack_Head = NULL;
	//	Stack_Head->Next = NULL;

	head_open_node->node = NULL;
	head_open_node->Next = NULL;
	head_close_node->node = NULL;
	head_close_node->Next = NULL;
	end_open_node->node = NULL;
	end_open_node->Next = NULL;
	end_close_node->node = NULL;
	end_close_node->Next = NULL;
}