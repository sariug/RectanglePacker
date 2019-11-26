#pragma once
#include <iostream>
#include <string>
#include <vector>

using Corners = std::vector<int>;
class Rect
{
public:
	Rect();
	Rect(int w, int h);
	Rect(int X, int Y, int W, int H);
	int area() const;
	std::string print_matlab();
	void print();
	std::string print_csv();

	int get_width() const;
	int get_height() const;
	Corners get_corners();
	void setloc(int X, int Y);
	bool is_set();
	void set_false();

private:
	int x;
	int y;
	int width;
	int height;
	bool located = false;
};
