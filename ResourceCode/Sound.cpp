#include "Standard.h"

SoundInfo::SoundInfo()
{

}

SoundInfo::~SoundInfo()
{

}

void SoundInfo::SetInfo(char* str)
{
	char buf[64] = {0};
	strcpy_s(buf, 64, str);
}

char* SoundInfo::GetSoundName()
{
	return name;
}

///////////////////

SoundManager::SoundManager()
{
	max_id = 10;
	now_id = 0;
}

SoundManager::~SoundManager()
{
	//gtool_bgmDestroy(gt);
}

void SoundManager::InitSound()
{
	char buf[MAX_CHAR_BUF];
	int len = MUSICMANAGER.GetMaxMusicCount();
	for(int i = 0 ; i < len ; i++)
	{
		sprintf_s(buf, MAX_CHAR_BUF, "%s%s.mp3", SOUND_PATH,  MUSICMANAGER.mi[i].name);
		gtool_bgmLoad(gt,now_id, buf);
		memset(buf,'\0',MAX_CHAR_BUF);
		MUSICMANAGER.mi[i].snd_id = now_id;
		now_id++;
	}
}

void SoundManager::SoundPlay(int sid)
{
	gtool_bgmPlay(gt, sid);
}

void SoundManager::SoundStop(int sid)
{
	gtool_bgmPause(gt, sid);
	gtool_bgmHome(gt, sid);
}

int SoundManager::AddSound(char *name)
{
	if(now_id == max_id-1) return 0;

	gtool_bgmLoad(gt, now_id,name);
	now_id++;

	return 1;
}

int SoundManager::PlaySoundInit()
{
	ifstream fp;
	fp.open("Music/List.txt");
	fp >> max_sound;
	max_sound++;

	char buf[100];

	for(int i = 0 ; i < max_sound; i++)
	{
		fp >> buf;
	/*	sprintf(si[i].path, "Music/Sound/%s.mp3", buf);
		sprintf(si[i].name, "%s", buf);
		sprintf(si[i].pattern, "Music/note/%s.txt", buf);*/
		si[i].SetInfo(buf);
		/*si[i].AddImage();*/

		//	gtool_PaperAdd(gt, si[i].disc);
	
		//	DiscImage[i-1] = gtool_SpriteLoad(gt,si[i].spg);

		//si[i].sid = i;
		//AddSound(si[i].path);
	}

	fp.close();

	return 1;
}

char* SoundManager::GetSoundName(int sid)
{
	return si[sid].GetSoundName();
}
