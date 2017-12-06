#pragma once
#include <vector>

template<class T>
class AssetArray
{
private:
	std::vector<T*> assetArray;
	int iLength;
	T* GetIndexed(int);
public:
	AssetArray();
	~AssetArray();
	int Gen();
	template<class N> int Gen();
	T* Del(int);
	T* Get(int);
	bool IsInRange(int);
};