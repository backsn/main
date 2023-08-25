#ifndef __PLAYSCENE__
#define __PLAYSCENE__

struct NOTEINFO
{
	int state;
	int type;
	int length;
	void Clear()
	{
		state = -1;
		type  = -1;
		length = -1;
	}
};

struct LINEINFO
{
	int state;
	//int note[16];
	NOTEINFO note[16];
	int x;
	float y;
};

struct NODEINFO
{
	int _bpm;
	int _bit;
	LINEINFO *LineInfo;
};

struct PLAYMUSICINFO
{
	int base_bit;
	int max_nodes;
	NODEINFO *NodeInfo;
	MusicInfo *musicinfo;
};

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	int EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	void SceneBegin();
	void SceneEnd();

	int Draw();
	int Process();
	void Frames();

	void MouseMove(int x, int y);

private:
	int	frm;
	int bfrm;

	float speed;
	float scroll_speed;

	int max_line;
	int now_line;
	int now_node;
	int max_node;
	int note_line;
	int SelectIcon;

	PLAYMUSICINFO PlayMusicInfo;
	LINEINFO *line;
	int state;
	float now_scroll;
	gtool_State *p_gt;
};

#endif