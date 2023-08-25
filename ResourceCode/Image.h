#ifndef __IMAGE__
#define __IMAGE__

struct Frames
{
	int index;
	int frame;	
};

enum
{
	INTERFACE_DRAW = 0	,
	BGA_DRAW			,
	COURSE_BGA_DRAW		,
	ETC_DRAW			,
};

class Image
{
	private:
		sprite_Group *img;
		paper_Object *_img;

		int frame;
		char name[32];
		int type;
		POINT p;
		Frames frm_info;
		int opt;

	public:
		Image();
		~Image();
		void AddImage(char *str, int type);
		void SetImageOpt(int nopt = 0, int x = 0, int y = 0);
		void Draw(int x, int y, int frm = BS_INVAILD, int nopt = BS_INVAILD, int xx = 1024, int yy = 800, int al = 0, float rot = 0);
};

class ImageManager
{
private:
	Image **Image_Interface;
	Image **Image_BGA;
	Image **Image_ETC;
	Image **Image_Course;

	int max_image;
	int now_etc_image;
	int now_bgaimage;
	int now_interfaceimage;
	int now_courseimage;

	int frame;
	
public:
	ImageManager();
	~ImageManager();

	void	Process();
	
	void	InitImage(int max);
	void	SetImage();

	bool	DelImage(int type, char* name);
	bool	ReleaseImage(int type);
	int		GetImageIndex(int type, char* name);

	bool	AddImage(int type, int img_type, char* name, int nopt, int x, int y);

	void	Draw(int type, int index, int x, int y, int frm, int nopt = -1, int xx = 1024, int yy = 800, int al = 0, float rot = 0);

/*	void	Interface_Draw(int index, int x, int y, int frm, int nopt = -1, int xx = 1024, int yy = 800);
	void	Objcet_Draw(int index, int x, int y, int nopt = -1, int xx = 1024, int yy = 800);
	void	BGA_Draw(int index, int x, int y, int frm, int nopt = -1, int xx = 1024, int yy = 800);

	bool	AddInterfaceImage( char* name, int nopt, int x, int y);
	bool	AddIBGAImage( char* name, int nopt, int x, int y);
	bool	AddOBImage( char* name, int nopt, int x, int y);*/
};

#endif