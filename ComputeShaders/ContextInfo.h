#ifndef CONTEXTINFO_H
#define CONTEXTINFO_H

#include "Common.h"

struct ContextInfo
{
public:
	ContextInfo();
	ContextInfo(int majorVersion, int minorVersion, bool isCore);
	ContextInfo(const ContextInfo& other);
	void operator=(const ContextInfo& other);

	// Members
	int MajorVersion, MinorVersion;
	bool Core;
};

#endif // CONTEXTINFO_H