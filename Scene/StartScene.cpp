#include "Standard.h"

StartScene::StartScene()
{

}

StartScene::~StartScene()
{

}

void StartScene::SceneBegin()
{
	frm = 0;
	back_frm = 0;
	gtool_TextFontSet(gt, NULL, 5000, false, false, false);
	GameOption.Clear();
	//SDM.InitSound();
	//SDM.AddSound("Music/Sound/Doll's Garden.mp3");
	//SDM.SoundPlay(0);
}

void StartScene::SceneEnd()
{
//	SDM.SoundStop(0);
}

int StartScene::Process()
{
	if(!back_frm) frm++;
	if(frm == 55) back_frm = 1;
	if(back_frm) frm--;
	if(frm == 0) back_frm = 0;
	return 0;
}

int StartScene::EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_LBUTTONDOWN:
	//		SM.SceneChange(1, 1);
			return 0;

		case WM_RBUTTONDOWN:
			return 0;

		case WM_MOUSEMOVE:
			return 0;

		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_RETURN:
					SCENEMANAGER.SceneChange(1, 1);
					break;

				case VK_F1:
					{
						GameOption.GameMode = EV_14K_MANIAC;
						GameOption.GameStage = 0;
						GameOption.SelectMusic = 6;
						GameOption.SelectCourse = 0;
						SCENEMANAGER.SceneChange(PLAY_SCENE);
					}
					break;
			}
			return 0;
	}
	return 1;
}

int StartScene::Draw()
{
	IMAGEMANAGER.Draw(INTERFACE_DRAW, 1, 0, 0, 0, 1);
	return 0;
}

void StartScene::Frames()
{

}



