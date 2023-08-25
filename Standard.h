#pragma once
#include "gtool2u.h"

#include <mmsystem.h>
#include <mmreg.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
//#include <list.h>
#include <fstream>
#include <string.h>
//#include <iostream>
using namespace std;

#include "GameMain.h"
#include "Network.h"
#include "AIgorithm.h"
#include "Tool.h"
#include "Define.h"

#include "math.h"
#include "Scene.h"
#include "StartScene.h"
#include "Image.h"
#include "MusicInfo.h"
#include "SelectModeScene.h"
#include "SelectMusicScene.h"
#include "SelectCourseScene.h"
#include "Sound.h"
#include "LoginScene.h"
#include "MainScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern gtool_State *gt;
extern SceneManager SCENEMANAGER;
extern ImageManager IMAGEMANAGER;
extern MusicManager MUSICMANAGER;
extern SoundManager SOUNDMANAGER;

extern POINT mouse;
extern POINT pt;
extern int standardp;
extern int scratch;

extern game_option GameOption;
