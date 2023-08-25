#define MAX_CHAR_BUF 64
#define MAX_NAME_BUF 32
#define MAX_SOUND 12

#define BS_INVAILD -1

#define MAX_MODE_COUNT 8

#define MAX_MUSIC_COUNT 30

#define START_COURSE_COUNT 20

enum PLAYLINE
{
	MAX_5K_ONLY_LINE = 5,
	MAX_5K_LINE = 7,
	MAX_7K_LINE = 9,
	MAX_CATCH_LINE = 12,
	MAX_10K_LINE_EC = 12,
	MAX_10K_LINE = 13,
	MAX_14K_LINE = 16,
};

enum SCENE_LIST
{
	START_SCENE	= 0		,
	LOGIN_SCNEN			,
	MAIN_SCENE			,
	SELECTMODE_SCENE	,
	SELECTMUSIC_SCENE	,
	SELECTCOURSE_SCENE	,
	PLAY_SCENE			,
	MAX_SCENE			,
};

struct game_option
{
	int GameMode;
	int GameStage;
	
	int BSkin;
	int NSkin;
	int RandomState;
	int FadeOption;
	int VisualOption;
	int AutoOption;

	int SelectMusic;
	int SelectCourse;

	void Clear()
	{
		GameMode = -1;
		GameStage = -1;
		BSkin = 0;
		NSkin = 0;
		RandomState = 0;
		FadeOption = 0;
		VisualOption = 0;
		AutoOption = 0;
		SelectMusic = -1;
		SelectCourse = -1;
	}
};
