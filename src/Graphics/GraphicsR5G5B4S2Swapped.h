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

class GraphicsR5G5B4S2Swapped: public Graphics<ColorR5G5B4A2, unsigned short>
{
	public:
	typedef unsigned short InternalColor;
	static const InternalColor RGBMask = 0x3fff;
	InternalColor SBits;

	GraphicsR5G5B4S2Swapped()
	{
		SBits = 0xc000;
		frontColor = 0xffff;
	}

	virtual void dotFast(int x, int y, Color color)
	{
		backBuffer[y][x^1] = (color & RGBMask) | SBits;
	}

	virtual Color getFast(int x, int y)
	{
		return backBuffer[y][x^1] & RGBMask;
	}

	virtual InternalColor** allocateFrameBuffer()
	{
		return Graphics::allocateFrameBuffer(xres, yres, (InternalColor)SBits);
	}
};
