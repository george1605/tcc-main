#ifndef __VIDEO_H__
#define __VIDEO_H__
#include <stdint.h>

struct __VBEData;
typedef struct __VBEData VBEData;

typedef struct
{
	uint16_t width, height;
	int16_t leftOffs, topOffs;
	const uint32_t* bitmap;
	bool m_transparency;//optimization
	
	bool m_resizeMode;
	uint16_t boundsWidth, boundsHeight;
}
Cursor;

enum
{
	CLICK_LEFT,
	CLICK_RIGHT,
	CLICK_LEFTD,
	CLICK_LEFTR,
	CLICK_RIGHTD,
	CLICK_RIGHTR,
};

typedef struct
{
	int clickType, clickedAtX, clickedAtY;
}
ClickInfo;

typedef struct
{
	int left, top, right, bottom;
}
Rectangle;

typedef struct
{
	int x, y;
}
Point;

typedef struct
{
	short width, height;
	const uint32_t *framebuffer;
}
Image;

#endif