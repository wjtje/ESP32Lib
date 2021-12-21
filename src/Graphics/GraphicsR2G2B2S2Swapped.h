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

class GraphicsR2G2B2S2Swapped: public Graphics<unsigned char>
{
	public:
	typedef unsigned char Color;
	static const Color RGBAXMask = 0x3f;
	Color SBits;
	
	GraphicsR2G2B2S2Swapped()
	{
		SBits = 0xc0;
	}

	virtual Color RGBA(int r, int g, int b, int a = 255) const
	{
		return ((r >> 6) & 0b11) | ((g >> 4) & 0b1100) | ((b >> 2) & 0b110000) | (a & 0b11000000);
	}

	virtual void dot(int x, int y, Color color)
	{
		if ((unsigned int)x < xres && (unsigned int)y < yres)
			backBuffer[y][x^2] = (color & RGBAXMask) | SBits;
	}

	virtual Color** allocateFrameBuffer()
	{
		return Graphics<Color>::allocateFrameBuffer(xres, yres, (Color)SBits);
	}
};