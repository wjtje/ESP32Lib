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

class GraphicsW8RangedSwapped: public Graphics<ColorW8, unsigned char>
{
	public:
	typedef unsigned char InternalColor;
	int colorDepthConversionFactor = 256;
	int colorMinValue = 0;
	int colorMaxValue = 255;

	GraphicsW8RangedSwapped()
	{
		frontColor = 0xff;
	}

	virtual void dotFast(int x, int y, Color color)
	{
		backBuffer[y][x^2] = (InternalColor)((colorMinValue<<8) + colorDepthConversionFactor*(int)color)>>8;
	}

	virtual Color getFast(int x, int y)
	{
		return (Color)((((int)backBuffer[y][x^2] << 8) - (colorMinValue<<8)) / colorDepthConversionFactor);
	}

	virtual InternalColor** allocateFrameBuffer()
	{
		return Graphics::allocateFrameBuffer(xres, yres, (InternalColor)colorMinValue);
	}

	virtual void clear(Color color = 0)
	{
		InternalColor newColor = (InternalColor)((colorMinValue<<8) + colorDepthConversionFactor*(int)color)>>8;
		for (int y = 0; y < this->yres; y++)
			for (int x = 0; x < this->xres; x++)
				backBuffer[y][x] = newColor;
	}
};
