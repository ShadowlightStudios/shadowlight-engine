#include "stdafx.h"
#include "Lump.h"

Lump::Lump()
{
	loaded = false;
	index = -1;
	parent = NULL;
	contentType = LT_EMPTY;
	subLumps.clear();
}

// Inserts a lump under this lump
bool Lump::Insert(const Lump& lumpIn)
{
	// If the key does not exist, carry on
	if (subLumps.find(lumpIn.name) == subLumps.end())
	{
		subLumps.insert(make_pair(lumpIn.name, lumpIn));
		return true;
	}
	// Otherwise, this lump already exists, and we can exit with false
	else
		return false;
}

Lump* Lump::Find(string lumpName)
{
	map<string, Lump>::iterator iter;
	if ((iter = subLumps.find(lumpName)) == subLumps.end())
	{
		return NULL;
	}
	else
	{
		// Return the pointer to the sub-lump at lumpName
		return &(iter->second);
	}
}
// Destroys the sub-lumps
Lump::~Lump()
{
	subLumps.clear();
}