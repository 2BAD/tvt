#ifndef _DISPLAY_DEFINE_H_
#define _DISPLAY_DEFINE_H_
//#include "dvrdvstypedef.h"

//设计固定层数：标准分割层、画中画层
enum LAYOUT_LAYER
{
	LAYOUT_LAYER_0,
	LAYOUT_LAYER_1,
};

enum STREAM_TYPE
{
	STREAM_TYPE_NONE,
	STREAM_TYPE_LIVE,
	STREAM_TYPE_PLAYBACK = 100,
};

enum LAYOUT_PIP_POSITION
{
	LAYOUT_PIP_LEFT_TOP,
	LAYOUT_PIP_RIGHT_TOP,
	LAYOUT_PIP_LEFT_BOTTOM,
	LAYOUT_PIP_RIGHT_BOTTOM,
	LAYOUT_PIP_NUM,
};

enum CH_STATUS
{
	CH_STATUS_FREE		= 0,
	CH_STATUS_VLOSS		= 1,
	CH_STATUS_DISCONNECT= 2,
	CH_STATUS_NO_AUTH	= 3,
	CH_STATUS_RECORD	= 4
};

const unsigned int MAX_NORMAL_PORT_NUM = 128;
const unsigned int	MAX_DISPLAY_PORT_NUM = MAX_NORMAL_PORT_NUM + LAYOUT_PIP_NUM;
const unsigned int PIP_SIZE_PERCENT = 20;

const unsigned int PORT_STATUS_BAR_HEIGHT = 16;

#ifdef _WINDOWS_
typedef long                POINTERHANDLE;
#endif

typedef void (CALLBACK *DRAW_FUN_CALLBACK)(POINTERHANDLE lLiveHandle, HDC hDC, void *pUser);

typedef struct _display_port
{
	unsigned short index;	//区域编号
	unsigned short zOrder;	//Z轴显示顺序LAYOUT_LAYER

	unsigned short xPos;	//左上角横坐标
	unsigned short yPos;	//左上角纵坐标
	unsigned short cx;		//显示区域宽度（像素）
	unsigned short cy;		//显示区域高度（像素）

	unsigned short channel;
	unsigned short streamType;//STREAM_TYPE
	unsigned int deviceID;
	unsigned int liveHandle;
	DRAW_FUN_CALLBACK	drawCallBackFunc;
	void *				cbParam;
}DISPLAY_PORT;

typedef enum
{
    FISHEYE_ORIGNAL = 0,		        //原始模式,即顶/壁/底装模式下的鱼眼图,相当于退出鱼眼校正模式

    FISHEYE_ROOF = 0x0100,		        //顶装(吸顶)
//    FISHEYE_ROOF_360,			        //顶装之360°矩形展开全景 + 独立子画面;子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景还支持左右起始点移动操作
    FISHEYE_ROOF_2x180 = 0x0102,		//顶装之2个关联的180°矩形展开画面，任何时刻两子窗口均组成360°全景，又叫“双全景”，两个矩形展开画面均支持左右移动起始点操作，并相互联动;
    FISHEYE_ROOF_FISH_3PTZ,		        //顶装之原始图像 + 3个独立子画面，子画面和原始图像中的子框均支持变倍、移动操作，原始图像还支持旋转改变起始点操作;
    FISHEYE_ROOF_FISH_4PTZ,		        //项装之原始图像 + 4个独立子画面，子画面和原始图像中的子框均支持变倍、移动操作，原始图像还支持旋转改变起始点操作
//    FISHEYE_ROOF_360_6PTZ,		    //项装之360°矩形展开全景 + 6个独立子画面，子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景还支持左右起始点移动操作;
    FISHEYE_ROOF_FISH_8PTZ = 0x0106,    //项装之原始图像 + 8个独立子画面，子画面和原始图像中的子框均支持变倍、移动操作，原始图像还支持旋转改变起始点操作;

    FISHEYE_WALL = 0x0200,		        //壁装
    FISHEYE_WALL_180,			        //壁装之180全景图，从左到右180°矩形展开全景，180°矩形展开全景支持上下移动操作，改变垂直视角;
    FISHEYE_WALL_180_3PTZ,		        //壁装之180°矩形展开全景 + 3个独立子画面，子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景支持上下移动操作，改变垂直视角
    FISHEYE_WALL_180_4PTZ,		        //壁装之180°矩形展开全景 + 4个独立子画面，子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景支持上下移动操作，改变垂直视角
    FISHEYE_WALL_180_8PTZ,		        //壁装之180°矩形展开全景 + 8个独立子画面，子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景支持上下移动操作，改变垂直视角

    FISHEYE_DESKTOP = 0x0300,	        //底装(桌面)
//    FISHEYE_DESKTOP_360,		        //底装之360°矩形展开全景 + 独立子画面;子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景还支持左右起始点移动操作
    FISHEYE_DESKTOP_2x180 = 0x0302,		//底装之2个关联的180°矩形展开画面，任何时刻两子窗口均组成360°全景，又叫“双全景”，两个矩形展开画面均支持左右移动起始点操作，并相互联动;
    FISHEYE_DESKTOP_FISH_3PTZ,	        //底装之原始图像 + 3个独立子画面，子画面和原始图像中的子框均支持变倍、移动操作，原始图像还支持旋转改变起始点操作;
    FISHEYE_DESKTOP_FISH_4PTZ,	        //底装之原始图像 + 4个独立子画面，子画面和原始图像中的子框均支持变倍、移动操作，原始图像还支持旋转改变起始点操作
//    FISHEYE_DESKTOP_360_6PTZ,	        //底装之360°矩形展开全景 + 6个独立子画面，子画面和矩形展开全景中的子框均支持变倍、移动操作，矩形展开全景还支持左右起始点移动操作;
    FISHEYE_DESKTOP_FISH_8PTZ = 0x0306,	//底装之原始图像 + 8个独立子画面，子画面和原始图像中的子框均支持变倍、移动操作，原始图像还支持旋转改变起始点操作;

}FISHEYE_MODE;

//渲染类型
typedef enum tagRENDER_TYPE
{
    MP_RENDER_NOTSET = 0,				// 未设置
    MP_RENDER_DDRAW,					// ddraw渲染
    MP_RENDER_D3D,						// d3d渲染
    MP_RENDER_OPENGL,		            // 非windows平台opengl渲染
    MP_RENDER_SDL2,                    // SDL_AUTO
    MP_RENDER_SDL2_SOFTWARE,           // SDL_RENDERER_SOFTWARE
    MP_RENDER_SDL2_OCX = MP_RENDER_SDL2_SOFTWARE,                    // OCX use
    MP_RENDER_SDL2_FORLIBVA,
    MP_RENDER_CALLER                   //播放库只解码，回调YUV数据给caller自己渲染
}RENDER_TYPE;

#endif
