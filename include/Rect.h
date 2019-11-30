#pragma once
#include <iostream>
#include <string>
#include <vector>

class Rect
{
public:
	Rect() noexcept;
	Rect(int w, int h) noexcept;
	Rect(int X, int Y, int W, int H) noexcept;
	int area() const;
	std::string print_matlab();
	std::string print_csv();

	int get_width() const;
	int get_height() const;
	std::vector<int> get_corners();
	void setloc(const int &X, const int &Y);
	bool is_set();
	void set_false();
	friend std::ostream & operator << (std::ostream &out, const Rect &r);

private:
	int x=0;
	int y=0;
	int width=1;
	int height=1;
	bool located = false;
};
