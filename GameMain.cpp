#include "Standard.h"

GameMain::GameMain()
{
	gtool_frmInit(gt,40);
	//gtool_frmInit(gt, 150);
	m_Frame = 0;
	gtool_PaperCreate(gt,40);
	gtool_bgmCreate(gt, 20);
}

GameMain::~GameMain()
{
//	Destroy();
}

int GameMain::Init(HINSTANCE hInstance, int nCmdShow, POINT p)
{
	gtool_Initialize(gt,hInstance,nCmdShow);
	if(!gtool_CreateWorkSpace(gt,hInstance,"Pattern Simulator",p,false))
		return 1;

	is_turn_now = 0;
	turn_gap_frm =0;

	SCENEMANAGER.InitScene(7);
	SCENEMANAGER.AddScene(new StartScene);
	SCENEMANAGER.AddScene(new LoginScene);
	SCENEMANAGER.AddScene(new MainScene);
	SCENEMANAGER.AddScene(new SelectModeScene);
	SCENEMANAGER.AddScene(new SelectMusicScene);
	SCENEMANAGER.AddScene(new SelectCourseScene);
	SCENEMANAGER.AddScene(new PlayScene);
/*	SM.AddScene(new GameScene);
	SM.AddScene(new ResultScene);
	SM.AddScene(new GameOverScene);*/

	SCENEMANAGER.Start();
	IMAGEMANAGER.InitImage(40);

	MUSICMANAGER.SetMusicInfo();
	SOUNDMANAGER.InitSound();
	
	return 0;
}

void GameMain::Loop()
{
	while(gtool_Loop(gt))
	{
		GameNow();	
	}
}

void GameMain::Destroy()
{
	gtool_PaperRelease(gt);
	gtool_bgmDestroy(gt);
	gtool_Close(gt);
}

void GameMain::GameNow()
{
	static int time = 0;
	if(gtool_frmSkip(gt))	//Skip 가능한것들
	{
		gtool_DrawBegin(gt);
		IMAGEMANAGER.Draw(INTERFACE_DRAW, 0, 0, 0, 0, 1);
		
		SCENEMANAGER.Draw();

		// 게임 데이터를 바탕으로 화면에 그림
		gtool_DrawEnd(gt);
	}
	if(gtool_frmUpdate(gt))
	{
		SCENEMANAGER.Process();
		m_Frame++;
		if(m_Frame == 40)
		{
			m_Frame = 0;
			time++;
		}
		if(is_turn_now)
		{
			turn_gap_frm++;
			if(turn_gap_frm == 10) 
			{
				turn_gap_frm = 0;
				is_turn_now = 0;
			}
		}		
		Keyboard();
	}	
}

int GameMain::MessageProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{ //이벤트 프로시저 삽입
	switch(msg)
	{
	/*	case WM_DESTROY:
			gtool_PaperRelease(gt);
			return 0;*/

		case WM_MOUSEMOVE:
			standardp = mouse.x;
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
		
			if(standardp > mouse.x)
			{
				scratch--;
				if(scratch == -1) scratch = 500;
				is_turn_now= 1;
				SCENEMANAGER.ScratchLeftTurn();
					
			}
			if(standardp < mouse.x)
			{
				scratch++;
				if(scratch == 501) scratch = 0;
				is_turn_now= 1;
				SCENEMANAGER.ScratchRightTurn();
			}
	}

	return SCENEMANAGER.EventProcess( hWnd, msg, wParam, lParam);
}

void GameMain::Keyboard()
{
	if(gtool_KeyboardGet(gt,VK_LEFT))
	{
		if(pt.x != 0) pt.x+=10;
	}
	if(gtool_KeyboardGet(gt,VK_RIGHT))
	{
		if(pt.x != -790) pt.x-=10;
	}
	if(gtool_KeyboardGet(gt,VK_UP))
	{
		if(pt.y != 0) pt.y+=10;
	}
	if(gtool_KeyboardGet(gt,VK_DOWN))
	{
		if(pt.y != -600) pt.y-=10;
	}
}
