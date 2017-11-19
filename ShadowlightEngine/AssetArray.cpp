#include "stdafx.h"
#include "AssetArray.h"

// Simple constructor
template<class T>
AssetArray<T>::AssetArray()
{
	list = NULL;
}

// Get the pointer to an indexed asset
template<class T>
List<T>* AssetArray<T>::GetIndexed(int i)
{
	// NULL values are treated as nonexistent assets
	//
	// If the index is negative, return NULL
	if (i < 0)return NULL;
	// Keep track of the current list element
	List<T>* ptr;
	ptr = list;
	// Loop to search
	while (ptr)
	{
		// If this is the droid *cough cough* list element *cough cough*
		// we're looking for, break the loop with ptr pointing to the index
		if (i == 0)
			break;
		ptr = ptr->next;
		i--;
	}
	// If we didn't find it i.e. we hit a dead end in the list
	// the loop will exit with ptr as NULL, so return
	// and if it's NULL, it'll be invalid
	//
	// Also, if this list element doesn't contain an asset,
	// it'll return NULL
	return ptr;
}

// Generates a new asset and returns it's index
template<class T>
int AssetArray<T>::Gen()
{
	int i = 0;
	// Find an empty slot
	List<T>* ptr;
	while (true)
	{
		// If this is a blank asset
		if (!ptr->info)
		{
			// Exit the loop with it
			break;
		}
		// If this is a dead end
		if (!ptr->next)
		{
			// Create a new one, exit with it
			ptr->next = new List<T>;
			ptr = ptr->next;
			i++;
			// Initialize it
			ptr->next = NULL;
			ptr->info = NULL;
			// Exit
			break;
		}
		// Otherwise, increment the count and advance by one
		ptr = ptr->next;
		i++;
	}
	// Initialize a new asset
	ptr->info = new T;
	// And exit with the new index
	return i;
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
	List<T>* ret;
	T* info;
	ret = GetIndexed(index);
	// If it's NULL; invalid index
	// throw an exception
	if (!ret)
	{
		throw out_of_range;
	}
	// Keep a backup of the asset
	info = ptr->info;
	// Figure out how to move the pointers around it
	// Case 1: it's at the index zero
	if (index == 0)
	{
		// Move list
		list = ptr->next;
	}
	// Case 2: it's in the middle or end
	else
	{
		// Move the previous one to the next
		// If it's the end, it'll automatically get NULL
		GetIndexed(index - 1)->next = ptr->next;
	}
	// Delete the old asset list element, return the asset itself
	delete ptr;
	return info;
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
	// Start looping so we can clean up
	List<T>* ptr;
	ptr = list;
	while (ptr)
	{
		// Delete if this has an active asset in it
		if (ptr->info)
			delete[] ptr->info;
		// Advance by one
		list = ptr->next;
		// Delete the old one
		delete ptr;
		// Go one ahead
		ptr = list;
	}
	// list will already be set to NULL; safe to exit
	return;
}