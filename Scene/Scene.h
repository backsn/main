#ifndef __SCENE__
#define __SCENE__

#define MAX_OF_STACK 10

typedef struct
{
	int data[10];
	int p;
}SCENE_STACK;

class Scene
{
public:
	Scene(void);
	~Scene(void);
	
	// Install
	virtual int EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	virtual int Draw(void);
	virtual int Process(void);
	
	// Define
	virtual void SceneBegin(void);
	virtual void SceneEnd(void);
	
	/// 추가 
	virtual int ScratchLeftTurn(void);
	virtual int ScratchRightTurn(void);
	
private:
	
};

class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);
	
	void InitScene(int n);		//Scene들을 초기화
	void ReleaseScene(void);
	int AddScene(Scene* s);		//Scene를 삽입
// 	int SceneChange(int s);
	
	int EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	int Draw(void);
	int Process(void);
	
	void Start(void);
	void End(void);
	
	void SceneOn(int opt);
	void SceneOff(int opt);
	int SceneChange(int n, int opt = 1);
	int SceneCall(int n, int opt);
	int SceneReturn(int opt);
	int SceneInit(int opt);
	int DataMessenger(int val1, int val2, int val3, int val4, int val5, int val6);
	int GetData(int val);
	
	int ScratchLeftTurn(void);
	int ScratchRightTurn(void);
	
private:
	Scene **scene_arr;
	SCENE_STACK stack;
	int now_scene,max_scene;
	
	int SceneCommand;
	paper_Object *background;
	paper_Object *bl;
	
	int space[6];
};

#endif