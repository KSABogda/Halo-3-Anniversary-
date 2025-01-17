#pragma once

#ifndef __PRINGLE_DRAW_
#define __PRINGLE_DRAW_

#include "Vector.hpp"
#include "../Pointer.hpp"

#include <d3d9.h>

#define COLOR4I(r, g, b, a) ((int)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define COLOR3I(r, g, b) COLOR4I(r, g, b, 255)

namespace Pringle
{
	struct DrawVertex
	{
		FLOAT x, y, z, w;
		DWORD color;

		DrawVertex() : x(0), y(0), z(0), w(1.f), color(0) { };
		DrawVertex(float _x, float _y, float _z, float _w, uint32_t _color) : x(_x), y(_y), z(_z), w(_w), color(_color) { };
		DrawVertex(float _x, float _y, float _z, uint32_t _color) : DrawVertex(_x, _y, _z, 1.f, _color) { };
		DrawVertex(float _x, float _y, uint32_t _color) : DrawVertex(_x, _y, 0.f, 1.f, _color) { };
	};

	class Draw
	{
		LPDIRECT3DDEVICE9 device;
		LPDIRECT3DSTATEBLOCK9 state;
		int screenWidth;
		int screenHeight;

	public:
		Draw(LPDIRECT3DDEVICE9 device);
		~Draw();

		LPDIRECT3DDEVICE9 GetDevice() const;

		int GetScreenWidth();
		int GetScreenHeight();

		void CaptureState();
		void ReleaseState();

		void Line(int sx, int sy, int ex, int ey, uint32_t color);
		void Rect(int x, int y, int w, int h, uint32_t color);
		void OutlinedRect(int x, int y, int w, int h, uint32_t color);

		void Text(const char* text, int x, int y, uint32_t color, uint32_t alignment = DT_LEFT | DT_BOTTOM);
		void Text(const wchar_t* text, int x, int y, uint32_t color, uint32_t alignment = DT_LEFT | DT_BOTTOM);

		bool ToScreen(float x, float y, float z, int& screenX, int& screenY, float clamp = 0.f);
	};
}

#endif //__PRINGLE_DRAW_