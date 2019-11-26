#pragma once
#include "RectLoader.h"
class PackNode
{
public:
	PackNode();
	PackNode(int X, int Y, int W, int H);

	std::vector<PackNode> children;
	int x, y, w, h;
	bool is_full;
	PackNode* insert(Rect& R);
	void extend(int);
}; 
