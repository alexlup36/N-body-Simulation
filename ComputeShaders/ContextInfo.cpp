#include "ContextInfo.h"


ContextInfo::ContextInfo()
{
	// Default constructor
	this->Core = true;
	this->MajorVersion = 3;
	this->MinorVersion = 3;
}

ContextInfo::ContextInfo(int majorVersion, int minorVersion, bool isCore)
{
	// Constructor
	this->Core = isCore;
	this->MajorVersion = majorVersion;
	this->MinorVersion = minorVersion;
}

ContextInfo::ContextInfo(const ContextInfo& other)
{
	// Copy constructor
	this->Core = other.Core;
	this->MajorVersion = other.MajorVersion;
	this->MinorVersion = other.MinorVersion;
}

void ContextInfo::operator=(const ContextInfo& other)
{
	// Assignment operator
	this->Core = other.Core;
	this->MajorVersion = other.MajorVersion;
	this->MinorVersion = other.MinorVersion;
}