#pragma once
#include "stdafx.h"

template<class T>
struct List
{
	T* info;
	List<T> next;
};

template<class T>
class AssetArray
{
private:
	List<T>* list;
	List<T>* GetIndexed(int);
public:
	AssetArray();
	~AssetArray();
	int Gen();
	T* Del(int);
	T* Get(int);
	bool IsInRange(int);
};