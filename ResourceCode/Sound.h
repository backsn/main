#ifndef __SOUND__
#define __SOUND__

//#define SOUND_PATH "Resource/Sound/%s.mp3"

class SoundInfo
{
	public:
		SoundInfo();
		~SoundInfo();
 		void SetInfo(char* str);
		char* GetSoundName();

	private:
		int sid;
		char name[MAX_CHAR_BUF];
// 		char path[MAX_CHAR_BUF];
// 		char pattern[MAX_CHAR_BUF];
// 		char disc[MAX_CHAR_BUF];
};

class SoundManager 
{
public:
	SoundManager();
	~SoundManager();
	void InitSound();

	void	SoundPlay(int sid);
	void	SoundStop(int sid);
	int		AddSound(char *name);

	int PlaySoundInit();
	char* GetSoundName(int sid);
/*	char* GetSoundPath(int sid);*/
/*	char* GetSoundPatern(int sid);*/

private:
	SoundInfo	si[MAX_SOUND];
	SoundInfo	bgm[MAX_SOUND];

	int max_id;
	int now_id;
	int max_sound;
};	

#endif