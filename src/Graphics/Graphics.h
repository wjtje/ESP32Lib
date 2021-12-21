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
#include <stdlib.h>
#include <math.h>
#include "../Tools/Log.h"

template<typename Color>
class Graphics
{
  public:
	int frameBufferCount;
	int currentFrameBuffer;
	Color **frameBuffers[3];
	Color **frontBuffer;
	Color **backBuffer;

	int xres;
	int yres;

	virtual void dot(int x, int y, Color color) = 0;
	virtual Color** allocateFrameBuffer() = 0;
	virtual Color** allocateFrameBuffer(int xres, int yres, Color value)
	{
		Color** frame = (Color **)malloc(yres * sizeof(Color *));
		if(!frame)
			ERROR("Not enough memory for frame buffer");				
		for (int y = 0; y < yres; y++)
		{
			frame[y] = (Color *)malloc(xres * sizeof(Color));
			if(!frame[y])
				ERROR("Not enough memory for frame buffer");
			for (int x = 0; x < xres; x++)
				frame[y][x] = value;
		}
		return frame;
	}
	virtual Color RGBA(int r, int g, int b, int a = 255) const = 0;

	void setFrameBufferCount(unsigned char i)
	{
		frameBufferCount = i > 3 ? 3 : i;
	}

	virtual void show(bool vSync = false)
	{
		if(!frameBufferCount)
			return;
		currentFrameBuffer = (currentFrameBuffer + 1) % frameBufferCount;
		frontBuffer = frameBuffers[currentFrameBuffer];
		backBuffer = frameBuffers[(currentFrameBuffer + frameBufferCount - 1) % frameBufferCount];
	}

	Graphics(int xres = 0, int yres = 0)
	{
		this->xres = xres;
		this->yres = yres;
		frameBufferCount = 1;
		for(int i = 0; i < 3; i++)
			frameBuffers[i] = 0;
		frontBuffer = 0;
		backBuffer = 0;
	}

	virtual bool allocateFrameBuffers()
	{
		if(yres <= 0 || xres <= 0)
			return false;
		for(int i = 0; i < frameBufferCount; i++)
			frameBuffers[i] = allocateFrameBuffer();
		currentFrameBuffer = 0;
		show();
		return true;
	}

	virtual void setResolution(int xres, int yres)
	{
		this->xres = xres;
		this->yres = yres;
		allocateFrameBuffers();
	}

	virtual float pixelAspect() const
	{
		return 1;
	}
};
