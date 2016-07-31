#include "FrameBufferInfo.h"


FrameBufferInfo::FrameBufferInfo()
{
	this->EnableMSAA = false;
	this->EnableSRGB = false;
	this->MSAASampleCount = 0;
}

FrameBufferInfo::FrameBufferInfo(bool msaa, bool srgb, bool vsync, int msaaSampleCount)
{
	this->EnableMSAA = msaa;
	this->EnableSRGB = srgb;
	this->EnableVSync = vsync;
	this->MSAASampleCount = msaaSampleCount;	
}
