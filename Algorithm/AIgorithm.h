#ifndef __ALGORITHM__
#define __ALGORITHM__
#include "windows.h"

struct Road
{
	int value;             // 평가치
	int degree;            // 깊이
	POINT p;               // 좌표 
	struct Road* Next;     // 다음 노드
	struct Road* Prev;     // 이전 노드
	struct Road* direct[4];// 4방향 노드 
	int turncount;         // 방향변경횟수
	int prev_dir;          // 이전에 진행했던 방향 
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
	int SetDirection(POINT start, POINT des);									// 시작점과 목적점 주위 4방향을 조사하고 시작점에서의 목점점 방향을 검사 
	BOOL CheckNaver(POINT p);													// 주위 4칸을 체크한다.
	BOOL Root(POINT next, POINT des, int dir);									// 시작점에서 4방향을 뿌리내려 검색 시작 

	BOOL RootSearch(Road* dir_R, Road* R_prev, POINT now, POINT des, int prev_dir, int dir, int count);// 4방향을 검색 
	void SetStart(POINT start);                                              // 시작
	BOOL CheckBox(POINT p, int dir);                                         // 20*10 범위에서 벗어나는지 체크 
	BOOL CheckNear(POINT now, POINT des, int count);                         // 현재 포인트가 목적지 포인트랑 인접한지 체크
	BOOL SearchStart(POINT start, POINT des);                                // 검색 시작 
	int GetDirection(POINT now, POINT des);

	void ClearRep();
	void AddOpenNode(Road* R_node);                                          // 오픈노드로 등록 
	void AddCloseNode(Road* R_node);                                         // 클로즈노드로 등록 
	void RemoveOpenNode(Road* R_node);                                       // 오픈노드를 제거 
	BOOL CheckOpenNode(Road* R_node);                                        // 오픈노드인지를 판별 
	BOOL CheckCloseNode(Road* R_node);                                       // 클로즈노드인지를 판별 
	BOOL Check4Dir(int x, int y);                                            // 인자값이 빈칸인지를 검색

	BOOL CheckDirection(POINT now, POINT des, int dir, int count);         // 현재 좌표에서 목적지좌표까지 방향을 검색해
	// 현재 방향과 더불어 앞으로 몇번 꺽일건가를 조사
	POINT MakePoint(int x, int y);                                         // POINT 대용으로 일단만듬
	void AddStack(POINT p);

	void DrawLine(POINT p, int dir, int prev_dir);
	void SetLine(int deg);

private:
	POINT buf;
	POINT p;
	int direction[4];
	int start_dir[4]; // 0 아래 1 위 2 왼 3 오른 
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