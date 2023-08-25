#include "Standard.h"

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{
	for (int i = 0; i < max_node; i++)
	{
		for (int j = 0; j < PlayMusicInfo.NodeInfo[i]._bit; j++)
		{
			for (int k = 0; k < note_line; k++)
			{
				PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].Clear();
			}
			delete[]PlayMusicInfo.NodeInfo[i].LineInfo;
		}
		delete[]PlayMusicInfo.NodeInfo;
	}
}

void PlayScene::SceneBegin()
{
	state = 0;

	speed = 3.25f;
	scroll_speed = (float)(3.75f * (speed + 0.25) * 2 * speed / 15.0f/*14.1f*/);
	frm = 0;
	bfrm = 0;
	max_line = 0;
	now_line = 0;
	now_node = 0;
	max_node = 0;
	note_line = 0;
	now_scroll = 0.0f;

	PlayMusicInfo.musicinfo = &MUSICMANAGER.mi[GameOption.SelectMusic];

	switch (GameOption.GameMode)
	{
	case EV_14K_MANIAC:
		note_line = 16;
		break;

	default:
		note_line = 16;
		break;
	}

	char buf[MAX_CHAR_BUF];

	sprintf_s(buf, MAX_CHAR_BUF, "%s%s.txt", PATERN_PATH, PlayMusicInfo.musicinfo->name);

	ifstream fp;

	int bpm = 0, base_bit = 0, total_lines = 0, total_notes = 0, total_nodes = 0, start_term = 0;;
	float note_term = -15.0f;

	fp.open(buf);
	int temp = 0;
	fp >> bpm;
	fp >> base_bit;
	fp >> start_term;
	fp >> temp;
	fp >> temp;
	fp >> temp;
	fp >> total_lines;
	fp >> total_nodes;

	max_node = total_nodes;
	max_line = total_lines;

	float bmpb = bpm / 60.0f;
	scroll_speed = scroll_speed * bmpb;
	start_term = start_term * bmpb;

	PlayMusicInfo.NodeInfo = new NODEINFO[total_nodes];

	for (int i = 0; i < total_nodes; i++)
	{
		fp >> PlayMusicInfo.NodeInfo[i]._bpm;
		fp >> PlayMusicInfo.NodeInfo[i]._bit;
		PlayMusicInfo.NodeInfo[i].LineInfo = new LINEINFO[PlayMusicInfo.NodeInfo[i]._bit];

		base_bit = PlayMusicInfo.NodeInfo[i]._bit;
		switch (base_bit)
		{
		case 16:
			note_term = ((-3.75f) * (speed + 0.25f) * 2.0f);
			break;

		case 32:
			note_term = -7.5f;
			break;

		case 64:
			note_term = -3.75f;
			break;
		}

		for (int j = 0; j < PlayMusicInfo.NodeInfo[i]._bit; j++)
		{
			for (int k = 0; k < note_line; k++)
			{
				fp >> PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].length;
				if (PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].length > 0)
				{
					PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].state = 1;
					PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].type = 1;
				}
				if (PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].length > 1)
					PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].type = 2;
			}
			PlayMusicInfo.NodeInfo[i].LineInfo[j].x = 234;
			PlayMusicInfo.NodeInfo[i].LineInfo[j].y = (start_term + (note_term * j) + (i * note_term * PlayMusicInfo.NodeInfo[i]._bit)) * speed;
		}
	}

	fp.close();

	GameOption.SelectCourse = 0;
}

void PlayScene::SceneEnd()
{
	frm = 0;
}

int PlayScene::Process()
{
	frm++;

	if (frm % 8 == 0)
	{
		bfrm++;
		if (bfrm == 8)
		{
			bfrm = 0;
		}
	}

	switch (state)
	{
	case 0:
		if (frm > 120)
		{
			frm = 0;
			state = 1;
		}
		break;

	case 1:
	{
		now_scroll += scroll_speed;
		if (frm >= 120)
		{
			state = 2;
			frm = 0;
			SOUNDMANAGER.SoundPlay(GameOption.SelectMusic);
		}
	}
	break;

	case 2:
	{
		now_scroll += scroll_speed;

		for (int i = 0; i < PlayMusicInfo.NodeInfo[now_node]._bit; i++)
		{
			for (int j = 0; j < note_line; j++)
			{
				if (PlayMusicInfo.NodeInfo[now_node].LineInfo[i].y + now_scroll > 600)
					PlayMusicInfo.NodeInfo[now_node].LineInfo[i].note[j].state = 0;
			}
		}

		if (PlayMusicInfo.NodeInfo[now_node].LineInfo[PlayMusicInfo.NodeInfo[now_node]._bit - 1].y + now_scroll > 600)
		{
			now_node++;

			if (now_node >= max_node)
			{
				state = 3;
				frm = 0;
				gtool_bgmPause(gt, GameOption.SelectMusic);
				gtool_bgmHome(gt, GameOption.SelectMusic);
				break;
			}
		}
	}
	break;
	}
	return 0;
}

int PlayScene::EventProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:

			break;

		case VK_F1:
			//Effect(1);
			break;

		case VK_F2:
			now_scroll = 0;
			//Effect(2);
			break;

		case VK_F3:
			if (state == 2)
			{
				state = 4;
				gtool_bgmPause(gt, GameOption.SelectMusic);
				//gtool_bgmResume(a,b)	gtool_bgmCommand(a,b,BGM_RESUME)
			}
			else
			{
				state = 2;
				SOUNDMANAGER.SoundPlay(GameOption.SelectMusic);
			}
			//Effect(3);
			break;

		case VK_F4:
			if (speed != 1)
				speed--;
			//Effect(4);
			break;

		case VK_F5:
			if (speed != 5)
				speed++;
			//	Effect(5);
			break;

		case VK_F6:
			//	Effect(6);
			break;

		case VK_UP:
			//	if(opt.sel == 2) if(!turn) turn = 1;
			break;

		case VK_DOWN:
			//	if(opt.sel == 2) if(!turn) turn = 2;
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		return 0;

	case WM_LBUTTONUP:
		return 0;

	case WM_RBUTTONDOWN:
		return 0;

	case WM_MOUSEMOVE:
		MouseMove(mouse.x, mouse.y);
		return 0;

	case WM_MOUSEWHEEL:
		return 0;
	}
	return 1;
}

int PlayScene::Draw()
{
	int notecolor = 0;
	float notespace = 0;

	//IMAGEMANAGER.Draw(COURSE_BGA_DRAW, 0, 0, 0, 0, 1 );
	if (state == 0)
		IMAGEMANAGER.Draw(COURSE_BGA_DRAW, 1, 0, 0, 0, 1);
	else
		IMAGEMANAGER.Draw(BGA_DRAW, 0, 0, 0, bfrm, 1);

	if (state >= 1)
	{
		IMAGEMANAGER.Draw(INTERFACE_DRAW, 7, 169, 0, 6, 2, 650, 688, 225);
		IMAGEMANAGER.Draw(INTERFACE_DRAW, 7, 169, 0, 0, 1, 688);
	}

	if (state == 2 || state == 1 || state == 4)
	{
		for (int i = now_node; i < now_node + 2; i++)
		{
			for (int j = 0; j < PlayMusicInfo.NodeInfo[i]._bit; j++)
			{
				for (int k = 0; k < note_line; k++)
				{
					if (PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].type > 0 && PlayMusicInfo.NodeInfo[i].LineInfo[j].note[k].state > 0)
					{
						if (k > 9) notespace = 38;
						else notespace = 0;
						if (k == 0 || k == 15)
						{
							int aa = 0;
							if (k == 15) aa = 23;
							else aa = 0;
							IMAGEMANAGER.Draw(INTERFACE_DRAW, 7, (int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].x + k * 32 - 23 + aa + notespace),
								(int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].y + now_scroll - 22), 5, 1, 56, 56);
						}
						else if (k > 5 && k < 10)
						{
							IMAGEMANAGER.Draw(INTERFACE_DRAW, 7, (int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].x + k * 32 + 19),
								(int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].y + now_scroll), 4, 1, 35, 35);
						}
						else if (k == 2 || k == 4 || k == 11 || k == 13)
						{
							IMAGEMANAGER.Draw(INTERFACE_DRAW, 7, (int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].x + k * 32 + notespace),
								(int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].y + now_scroll), 2, 1, 34, 34);
						}
						else
						{
							IMAGEMANAGER.Draw(INTERFACE_DRAW, 7, (int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].x + k * 32 + notespace),
								(int)(PlayMusicInfo.NodeInfo[i].LineInfo[j].y + now_scroll), 3, 1, 34, 34);
						}

					}
				}
			}
		}
	}

	return 0;
}

void PlayScene::Frames()
{

}

void PlayScene::MouseMove(int x, int y)
{

}
