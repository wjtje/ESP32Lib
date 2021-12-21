/*
	Author: bitluni 2019
	License: 
	Creative Commons Attribution ShareAlike 4.0
	https://creativecommons.org/licenses/by-sa/4.0/
	
	For further details check out: 
		https://youtube.com/bitlunislab
		https://github.com/bitluni
		http://bitluni.net
*/
#pragma once
#include "Graphics.h"

class GraphicsR1G1B1A1X2S2Swapped: public Graphics<unsigned char>
{
	public:
	typedef unsigned char Color;
	static const Color RGBAXMask = 0x3f;
	Color SBits;
	
	GraphicsR1G1B1A1X2S2Swapped()
	{
		SBits = 0xc0;
	}

	virtual Color RGBA(int r, int g, int b, int a = 255) const
	{
		return ((r >> 7) & 1) | ((g >> 6) & 2) | ((b >> 5) & 4) | ((a >> 4) & 8);
	}

	virtual void dotFast(int x, int y, Color color)
	{
		backBuffer[y][x^2] = (color & RGBAXMask) | SBits;
	}
	
	virtual Color** allocateFrameBuffer()
	{
		return Graphics<Color>::allocateFrameBuffer(xres, yres, (Color)SBits);
	}
};