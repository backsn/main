#include "Standard.h"


SelectModeScene::SelectModeScene()
{

}

SelectModeScene::~SelectModeScene()
{

}

void SelectModeScene::SceneBegin()
{
	standardp = scratch = mouse.x;
	frm = 0;
	select = 0;
	turn = 0;
	animation = 0;
	ani_frm = 0;
	state =0;
}

void SelectModeScene::SceneEnd()
{

}

int SelectModeScene::Process()
{
	frm++;
	if(frm > 56) frm = 0;
	if(state)
	{
		animation -= 10;
		ani_frm++;
		if(ani_frm == 15) ani_frm =0;
		if(	animation < -259)
		{
			state = 2;
			SCENEMANAGER.SceneChange(SELECTMUSIC_SCENE, 0);
		}
	}

	if(!state)
		if(turn)
		{
			ani_frm++;
			if(turn == 1) 
			{
				animation += 23;

			}
			if(turn == 2)
			{
				animation -= 23;

			}
			if(ani_frm == 15) 
			{
				ani_frm = 0;
				animation = 0;
				if(turn == 1)
				{
					select--;
					if(select == -1) select = 8;
				}
				if(turn == 2)
				{
					select++;
					if(select == 9) select = 0;
				}
				turn = 0;
			}
		}
		return 0;
}

int SelectModeScene::EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		if(select == 8)
		{
			SelectMode();
			SCENEMANAGER.SceneChange(2, 0);
		}
		return 0;

	case WM_RBUTTONDOWN:

		return 0;

	case WM_MOUSEMOVE:

		return 0;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_RETURN:
			SCENEMANAGER.SceneChange(SELECTMUSIC_SCENE);
			break;
		case VK_LEFT:
			if(!turn)
				turn = 1;
			break;

		case VK_RIGHT:
			if(!turn)
				turn = 2;
			break;
		}
		return 0;
	}
	return 1;
}

int SelectModeScene::ScratchLeftTurn()
{
	return 0;
}

int SelectModeScene::ScratchRightTurn()
{
	return 0;
}

int SelectModeScene::Draw()
{
	if(state == 0)
	{
		IMAGEMANAGER.Draw(BGA_DRAW, 0, 0, 0, frm/8, 1);

		for(int i = 0 ; i < 5 ; i++)
		{
			if(i == 2) IMAGEMANAGER.Draw(INTERFACE_DRAW, 4,(-375 + i*344) + animation, 100, (7+i+select)%9, 1, 400, 400);
			else IMAGEMANAGER.Draw(INTERFACE_DRAW, 4,(-300 + i*344) + animation, 200, (7+i+select)%9);
		}
	}
	else
	{
		IMAGEMANAGER.Draw(INTERFACE_DRAW, 4, 388 + animation, 200, select);
	}

	return 0;
}

void SelectModeScene::Frames()
{

}

void SelectModeScene::SelectMode()
{
	state = 1;
	animation = 0;
}
