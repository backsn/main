#ifndef __RESULTSCENE__
#define __RESULTSCENE__

class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	int EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	void SceneBegin();
	void SceneEnd();

	int Draw();
	int Process();

	void Frames();

private:
	int	frm;
};

#endif