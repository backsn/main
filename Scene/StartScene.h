#ifndef __STARTSCENE__
#define __STARTSCENE__

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	int EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	void SceneBegin();
	void SceneEnd();

	int Draw();
	int Process();
	void Frames();

private:
	paper_Object *Title;
	sprite_Group *Start;
	int frm;
	int back_frm;
};

#endif