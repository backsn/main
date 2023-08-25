#include "Standard.h"

Image::Image()
{
	img		= NULL;
	_img	= NULL;
	frame	= 0;
	name[0]	= '\0';
	type	= BS_INVAILD;
	opt		= BS_INVAILD;
	frm_info.frame = 0;
	frm_info.index = 0;
	p.x		= 0;
	p.y		= 0;
};

Image::~Image()
{
	if(img != NULL)
		gtool_SpriteDel(gt, img);
	else if(_img != NULL)
		gtool_PaperDel(gt, name);

	frame	= 0;
	name[0]	= '\0';
	type	= BS_INVAILD;
	opt		= BS_INVAILD;
	frm_info.frame = 0;
	frm_info.index = 0;
	p.x		= 0;
	p.y		= 0;
};

void Image::AddImage(char *str,int type)
{
	char buf[32];
	opt = type;

	if(type == 0)
	{
		gtool_PaperAdd(gt, str);
		strcpy_s(name,32, str);
		strcpy_s(buf,32, str);
		strcat_s(buf,32, ".spg");
		img = gtool_SpriteLoad(gt, buf);
	}
	else
	{
		_img = gtool_PaperAdd(gt, str);
	}
}

void Image::SetImageOpt(int nopt /* = 0 */, int x /* = 0 */, int y /* = 0*/)
{
	//opt = nopt;
	p.x = x;
	p.y = y;
}

void Image::Draw(int x, int y, int frm, int nopt, int xx, int yy, int al, float rot)
{
	if(opt == 0)
	{
		switch(nopt)
		{
			case 0:
				break;
			case 1:
				gtool_SpritePut(gt, GPOINT(x, y), img,  frm, gtool_SpriteOption(gt,GPOINT(xx, yy)));
				break;

			case 2:
				gtool_SpritePut(gt, GPOINT(x, y), img,  frm, gtool_SpriteOption(gt,GPOINT(xx, yy), GCOLOR(al,255,255,255), rot, GPOINT(xx/2, yy/2)));
				break;

			default:
				gtool_SpritePut(gt, GPOINT(x, y), img,  frm);
				break;
		}
	}
	else
	{
		switch(nopt)
		{
		case 0:
			break;
		case 1:
			gtool_PaperPut(gt, GPOINT(x, y), _img, gtool_SpriteOption(gt,GPOINT(xx, yy)));
			break;

		case 2:
			gtool_PaperPut(gt, GPOINT(x, y), _img, gtool_SpriteOption(gt,GPOINT(xx, yy), GCOLOR(al,255,255,255)));
			break;

		default:
			gtool_PaperPut(gt,GPOINT(x, y), _img);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

ImageManager::ImageManager()
{
	frame = 0;
}

ImageManager::~ImageManager()
{
	DISPOSE(Image_Interface);
	DISPOSE(Image_BGA);
} 

void ImageManager::Process()
{
	frame++;
}

void ImageManager::InitImage(int max)
{
	CREATE(Image_Interface, Image*, 30);
	//CREATE(Image_ETC, Image*, 30);
	CREATE(Image_BGA, Image*, 30);
	CREATE(Image_Course, Image*, 30);
	max_image = max;
	now_etc_image = 0;
	now_bgaimage = 0;
	now_interfaceimage = 0;
	now_courseimage = 0;
	SetImage();
}

bool ImageManager::AddImage(int type, int img_type, char* name, int nopt, int x, int y)
{
	Image *p;
	CREATE(p, Image, 1);
	p->AddImage(name, img_type);
	p->SetImageOpt(nopt, x, y);
	switch(type)
	{
	case INTERFACE_DRAW:
		{
			Image_Interface[now_interfaceimage] = p;
			now_interfaceimage++;
		}
		break;
	case BGA_DRAW:
		{
			Image_BGA[now_bgaimage] = p;
			now_bgaimage++;
		}
		break;
	case COURSE_BGA_DRAW:
		{
			Image_Course[now_courseimage] = p;
			now_courseimage++;
		}
		break;
	case ETC_DRAW:
		{
			Image_ETC[now_etc_image] = p;
			now_etc_image++;
		}
		break;
	default:
		return false;
		break;
	}

return true;
}

void ImageManager::Draw(int type, int index, int x, int y, int frm, int nopt /* = -1 */, int xx /* = 1024 */, int yy /* = 800 */, int al, float rot)
{
	switch(type)
	{
	case INTERFACE_DRAW:
		if(Image_Interface[index] == NULL) return;
		Image_Interface[index]->Draw(x, y, frm, nopt, xx, yy, al, rot);
		break;

	case BGA_DRAW:
		if(Image_BGA[index] == NULL) return;
		Image_BGA[index]->Draw(x, y, frm, nopt, xx, yy, al, rot);
		break;

	case COURSE_BGA_DRAW:
		if(Image_Course[index] == NULL) return;
		Image_Course[index]->Draw(x, y, frm, nopt, xx, yy, al, rot);
		break;

	case ETC_DRAW:
		if(Image_ETC[index] == NULL) return;
		Image_ETC[index]->Draw(x, y, frm, nopt, xx, yy, al, rot);
		break;

	default:
		return;
		break;
	}
}

void ImageManager::SetImage()
{
	AddImage(BGA_DRAW		, 0, "GenericBGA"	, 1, 1024, 1024);
	AddImage(INTERFACE_DRAW	, 1, "PassScene"	, 1, 1024, 1024); // 0
	AddImage(INTERFACE_DRAW	, 1, "Title"		, 1, 1024, 1024); // 1
	AddImage(INTERFACE_DRAW	, 0, "LoginBG"		, 1, 1024, 1024); // 2
	AddImage(INTERFACE_DRAW	, 0, "MainIcon"		, 1, 1024, 1024); // 3
	AddImage(INTERFACE_DRAW	, 0, "modeselect"	, 1, 1024, 1024); // 4
	AddImage(INTERFACE_DRAW	, 0, "SelectAMusic"	, 1, 1024, 1024); // 5
	AddImage(INTERFACE_DRAW	, 0, "SelectCourse"	, 1, 1024, 1024); // 6
}
/*
void ImageManager::Objcet_Draw(int index, int x, int y, int nopt, int xx, int yy)
{
	Image_Object[index]->Draw(x, y, nopt, xx, yy);
}

void ImageManager::Interface_Draw(int index, int x, int y, int frm, int nopt, int xx, int yy)
{
	Image_Interface[index]->Draw(x, y, frm, nopt, xx, yy);
}

void ImageManager::BGA_Draw(int index, int x, int y, int frm, int nopt, int xx, int yy)
{
	Image_BGA[index]->Draw(x, y, frm, nopt, xx, yy);
}*/
