#ifndef __ALGORITHM__
#define __ALGORITHM__
#include "windows.h"

struct Road
{
	int value;             // ��ġ
	int degree;            // ����
	POINT p;               // ��ǥ 
	struct Road* Next;     // ���� ���
	struct Road* Prev;     // ���� ���
	struct Road* direct[4];// 4���� ��� 
	int turncount;         // ���⺯��Ƚ��
	int prev_dir;          // ������ �����ߴ� ���� 
};

struct stacks
{
	POINT p;
	struct stacks* Next;
};

struct set_nodes
{
	struct Road* node;
	struct set_nodes* Next;
};

struct datas
{
	RECT rt[20][10];
	int Block[20][10];
	int GetBlockInfo(int x, int y) { return Block[x][y]; }
};

class AIgorithm
{
public:
	AIgorithm();
	~AIgorithm();

	BOOL Start(POINT start, POINT des);
	void ClearDIR();
	void Destroy();
	int SetDirection(POINT start, POINT des);									// �������� ������ ���� 4������ �����ϰ� ������������ ������ ������ �˻� 
	BOOL CheckNaver(POINT p);													// ���� 4ĭ�� üũ�Ѵ�.
	BOOL Root(POINT next, POINT des, int dir);									// ���������� 4������ �Ѹ����� �˻� ���� 

	BOOL RootSearch(Road* dir_R, Road* R_prev, POINT now, POINT des, int prev_dir, int dir, int count);// 4������ �˻� 
	void SetStart(POINT start);                                              // ����
	BOOL CheckBox(POINT p, int dir);                                         // 20*10 �������� ������� üũ 
	BOOL CheckNear(POINT now, POINT des, int count);                         // ���� ����Ʈ�� ������ ����Ʈ�� �������� üũ
	BOOL SearchStart(POINT start, POINT des);                                // �˻� ���� 
	int GetDirection(POINT now, POINT des);

	void ClearRep();
	void AddOpenNode(Road* R_node);                                          // ���³��� ��� 
	void AddCloseNode(Road* R_node);                                         // Ŭ������� ��� 
	void RemoveOpenNode(Road* R_node);                                       // ���³�带 ���� 
	BOOL CheckOpenNode(Road* R_node);                                        // ���³�������� �Ǻ� 
	BOOL CheckCloseNode(Road* R_node);                                       // Ŭ������������ �Ǻ� 
	BOOL Check4Dir(int x, int y);                                            // ���ڰ��� ��ĭ������ �˻�

	BOOL CheckDirection(POINT now, POINT des, int dir, int count);         // ���� ��ǥ���� ��������ǥ���� ������ �˻���
	// ���� ����� ���Ҿ� ������ ��� ���ϰǰ��� ����
	POINT MakePoint(int x, int y);                                         // POINT ������� �ϴܸ���
	void AddStack(POINT p);

	void DrawLine(POINT p, int dir, int prev_dir);
	void SetLine(int deg);

private:
	POINT buf;
	POINT p;
	int direction[4];
	int start_dir[4]; // 0 �Ʒ� 1 �� 2 �� 3 ���� 
	int ch_dir;
	int now_dir;
	int count;

	POINT start_p;
	POINT des_p;

	Road* R;
	Road* R_head;
	stacks* Stack_End;
	stacks* Stack_Head;
	set_nodes* open_node;
	set_nodes* head_open_node;
	set_nodes* end_open_node;
	set_nodes* close_node;
	set_nodes* head_close_node;
	set_nodes* end_close_node;

	datas m_Board;
	datas* m_Sprite;
};

#endif