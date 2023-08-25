#ifndef __SelectModeScene__
#define __SelectModeScene__

class SelectModeScene : public Scene
{
public:
	SelectModeScene();
	~SelectModeScene();

	int EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	void SceneBegin();
	void SceneEnd();

	int Draw();
	int Process();

	void Frames();

	int ScratchLeftTurn();
	int ScratchRightTurn();

	void SelectMode();

private:
	int frm;
	int select;
	int turn;
	int animation;
	int ani_frm;
	int state;
};

#endif