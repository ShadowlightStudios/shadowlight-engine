#include "stdafx.h"
#include "AssetArray.h"

// Simple constructor
template<class T>
AssetArray<T>::AssetArray()
{
	// Set the length to 0
	iLength = 0;
}

// Get the pointer to an indexed asset
template<class T>
T* AssetArray<T>::GetIndexed(int i)
{
	// NULL values are treated as nonexistent assets

	// If the index is negative, return NULL
	if (i < 0)return NULL;

	// If it's longer then the length of the vector, return NULL
	if (i >= iLength) return NULL;

	// Return the index value
	return assetArray[i];
}

// Generate a new asset with type "T"
template<class T>
int AssetArray<T>::Gen()
{
	return Gen<T>();
}

// Generates a new asset and returns it's index
template<class T>
template<class N>
int AssetArray<T>::Gen()
{
	// Find an empty slot
	int i = 0;
	// Let's loop through all of the slots
	for (i = 0; i < iLength; i++)
	{
		// If this is a blank asset
		if (!assetArray[i])
		{
			// Exit with it
			assetArray[i] = new N;
			return i;
		}
	}
	// If we've made it this far, then there are no free slots
	// Push a new one
	assetArray.push_back(new N);
	return iLength;
}

// Grabs a pointer to the asset at 'index'
template<class T>
T* AssetArray<T>::Get(int index)
{
	List<T>* ret;
	ret = GetIndexed(index);
	// If it's NULL; invalid index
	// throw an exception
	if (!ret)
	{
		throw out_of_range;
	}
	// Otherwise, return the pointer
	return ret->info;
}

// Deletes the asset at 'index'
// Returns the asset that was there
// *** WARNING *** YOU MUST DELETE IT AFTERWARDS
template<class T>
T* AssetArray<T>::Del(int index)
{
	T* ret = Get(index);
	// Make sure that it's in-bounds before assigning NULL to it
	if (ret)
		assetArray[index] = NULL;
	return ret;
}

// Detects if index is in the asset list
template<class T>
bool AssetArray<T>::IsInRange(int index)
{
	// Simply return the conditional
	// of whether it found the index or not
	return GetIndexed(index) != NULL;
}

// Cleans up
template<class T>
AssetArray<T>::~AssetArray()
{
	// The list will clean itself up; just set the length to 0
	iLength = 0;
}