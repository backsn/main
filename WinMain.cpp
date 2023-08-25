#include "Standard.h"

gtool_State *gt;
GameMain	*GAMEMAIN;
SceneManager SCENEMANAGER;
ImageManager IMAGEMANAGER;
MusicManager MUSICMANAGER;
SoundManager SOUNDMANAGER;
game_option GameOption;
//MusicManager SDM;

POINT pt = {0};
POINT mouse = {0};
int scratch = 0;
int standardp = 0;

int MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return GAMEMAIN->MessageProc(hWnd, msg, wParam, lParam);
	
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	
	gt = gtool_Open();
	GAMEMAIN = new GameMain();
	POINT p; p.x = 1024; p.y = 800;
	
	if(GAMEMAIN->Init(hInstance, nCmdShow, p)) return -1;
	gtool_regEventProc(gt,MsgProc);
	
	GAMEMAIN->Loop();
	GAMEMAIN->Destroy();
	
	return 0;
}
