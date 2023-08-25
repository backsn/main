#include "Standard.h"

SceneManager::SceneManager(void)
{
	scene_arr = NULL;
	max_scene = now_scene = 0;
	memset(&stack,0,sizeof(stack));
	stack.p = -1;
}

SceneManager::~SceneManager(void)
{
	ReleaseScene();
	gtool_PaperDel(gt,"PassScene");
}

void SceneManager::InitScene(int n)
{
	ReleaseScene();
	scene_arr = new (Scene*[n]);
	max_scene = 0;
	now_scene = 0;
}

void SceneManager::ReleaseScene(void)
{
	int i=0;

	if(scene_arr != NULL)
	{
		for(i = 0; i < max_scene; i++)
			delete scene_arr[i];
		delete []scene_arr;
		
		scene_arr = NULL;
		max_scene = now_scene = 0;
	}
}

//Scene로 넘어오는 포인터의 메모리 관리는 직접하므로 생성자로 넘겨줄것
// 리턴 : Scene number
int SceneManager::AddScene(Scene* s)
{
	scene_arr[max_scene] = s;
	max_scene ++;

	return max_scene;
}

//Install

void SceneManager::Start(void)
{
	bl = gtool_PaperAdd(gt,"PassScene");
	stack.p = 0;
	SceneChange(0,0);
	Process();
}

void SceneManager::End(void)
{

}

int SceneManager::EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(stack.p != -1) return scene_arr[stack.data[stack.p]]->EventProcess(hWnd,msg,wParam,lParam);
	
	return 0;
}

int SceneManager::Draw(void)
{
	return scene_arr[stack.data[stack.p]]->Draw();
}

int SceneManager::Process(void)
{
//	if(stack.p == 0) gtool_Quit(gt);
	return scene_arr[stack.data[stack.p]]->Process();
}

// int SceneManager::SceneChange(int s)	
// {
// 	return 0;
// }

int SceneManager::SceneChange(int n, int opt)
{
	static int start = 0;
	
	//stack.data[stack.p] 에서 n 장면으로 전환. opt 방식으로 전환
	if(opt) SceneOff(opt);
	
	if(start) scene_arr[stack.data[stack.p]]->SceneEnd();
	if(start == 0) start = 1;
	
	stack.data[stack.p] = n;
	
	scene_arr[stack.data[stack.p]]->SceneBegin();
	if(opt) SceneOn(opt);
	return 0;
}

int SceneManager::SceneCall(int n, int opt)
{
	if(stack.p != -1)
		if(opt) SceneOff(opt);
	//stack overflow check
	if(stack.p >= MAX_OF_STACK)
	{
	//	MessageBox(NULL,"Scene Stack Overflow","SceneManager",0);
		return -1;
	}

	stack.data[stack.p + 1] = n;
	stack.p ++;

	//해당 n 스텍의 scene 초기화
	scene_arr[stack.data[stack.p]]->SceneBegin();
	//Change Animation
	if(stack.p != 0)
		if(opt) SceneOn(opt);
	//--end
	return 0;
}

int SceneManager::SceneReturn( int opt)
{
	if(stack.p <=0 )
		return -1;

	//해당 n 스텍의 scene 초기화
	scene_arr[stack.data[stack.p]]->SceneEnd();

	stack.p --;
	return 0;
}

int SceneManager::SceneInit( int opt)
{
	if(stack.p <=0 )
		return -1;
	if(opt) SceneOff(opt);

	for(int i = 0; i < stack.p ; i++)
		scene_arr[stack.data[stack.p]]->SceneEnd();

	SceneCall(0, 0);

	if(opt) SceneOn(opt);

	return 0;
}

int SceneManager::DataMessenger(int val1, int val2, int val3, int val4, int val5, int val6)
{
	space[0] = val1;
	space[1] = val2;
	space[2] = val3;
	space[3] = val4;
	space[4] = val5;
	space[5] = val6;
	return 0;
}

int SceneManager::GetData(int val)
{
	return space[val];
}

void SceneManager::SceneOn(int opt)
{
	int al = 255;

	while(gtool_Loop(gt))
	{
		if(gtool_frmUpdate(gt))
		{
			al -=4;
			if(al < 0) 
			{
				al = 0;
				break;
			}
		}
		if(gtool_frmSkip(gt))
		{
			gtool_DrawBegin(gt);
			scene_arr[stack.data[stack.p]]->Draw();
			gtool_PaperPut(gt,GPOINT(0,0),
				bl,
				gtool_SpriteOption(gt,GPOINT(1024,800),GCOLOR(al,255,255,255))
				);
			gtool_DrawEnd(gt);
		}
	}
}

void SceneManager::SceneOff(int opt)
{
	int al = 0;
	
	while(gtool_Loop(gt))
	{
		if(gtool_frmUpdate(gt))
		{
			al +=4;
			if(al > 255) 
			{
				al = 255;
				break;
			}
		}
		if(gtool_frmSkip(gt))
		{
			gtool_DrawBegin(gt);
		//	scene_arr[stack.data[stack.p]]->Draw();
			gtool_PaperPut(gt,GPOINT(0,0), bl, gtool_SpriteOption(gt,GPOINT(1024,800),GCOLOR(al,255,255,255)));
			gtool_DrawEnd(gt);
		}
	}
}


int SceneManager::ScratchLeftTurn()
{
	return scene_arr[stack.data[stack.p]]->ScratchLeftTurn();
}

int SceneManager::ScratchRightTurn()
{
	return scene_arr[stack.data[stack.p]]->ScratchRightTurn();
}


//--------------------------- Scene Driver (Default Templete)
Scene::Scene(void)
{	//Scene 클래스를 초기화합니다.

}

Scene::~Scene(void)
{	//Scene 클래스를 파괴합니다.

}

int Scene::EventProcess(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{	//이벤트 프로시저 삽입
	return 0;
}

int Scene::Draw(void)
{	//그리는 루틴을 집어넣습니다.
	return 0;
}

int Scene::Process(void)
{	//처리하는 루틴을 집어넣습니다.
	return 0;
}

void Scene::SceneBegin(void)
{	//Scene이 시작될때 데이터를 로드합니다.

}

void Scene::SceneEnd(void)
{	//Scene이 시작될때 데이터를 해제합니다.

}

int Scene::ScratchLeftTurn(void)
{
	return 0;
}

int Scene::ScratchRightTurn(void)
{
	return 0;
}