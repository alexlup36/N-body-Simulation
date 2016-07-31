#ifndef FRAMEBUFFERINFO_H
#define FRAMEBUFFERINFO_H

#include <SDL.h>

#include "Common.h"

struct FrameBufferInfo
{
public:
	FrameBufferInfo();
	FrameBufferInfo(bool msaa, bool srgb, bool vsync, int msaaSampleCount = 0);

	bool EnableMSAA;
	bool EnableSRGB;
	bool EnableVSync;
	int MSAASampleCount;
};

#endif // FRAMEBUFFERINFO_H