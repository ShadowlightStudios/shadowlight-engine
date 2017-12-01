#pragma once
#include <vector>

template<class T>
class AssetArray
{
private:
	std::vector<T*> assetArray;
	int iLength;
public:
	AssetArray();
	~AssetArray();
	int Gen();
	T* Del(int);
	T* Get(int);
	bool IsInRange(int);
};