#pragma once
#include <fstream>
#include <sstream>
#include "Rect.h"

class RectLoader
{
public:
	RectLoader(const std::string &filePath); 
	std::vector<Rect> load();
	void print_for_matlab(std::vector<Rect> &rects);
	void print_to_csv(std::vector<Rect> &rects);
	
private:
	std::string filepath;
};

