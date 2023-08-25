#ifndef __GAMEMAIN__
#define __GAMEMAIN__

class GameMain
{
public:
	GameMain();
	~GameMain();
	int MessageProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	
	int Init(HINSTANCE hInstance, int nCmdShow, POINT p);
	void Loop();
	void Destroy();
	
	void GameNow();
	void Keyboard();
	
private:
	int m_Frame;
	int is_turn_now;
	int turn_gap_frm;
};

#endif