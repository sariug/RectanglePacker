#pragma once
#include "Rect.h"

Rect::Rect(){};
Rect::Rect(int w, int h) : width(w), height(h)
{
	x = 0;
	y = 0;
}
Rect::Rect(int X, int Y, int W, int H) : x(X), y(Y), width(W), height(H) {}
int Rect::area() const { return width * height; }
std::string Rect::print_matlab()
{
	return "rectangle('Position', [" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + "]);\n";
}
std::string Rect::print_csv()
{
	return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(x+width) + ", " + std::to_string(y+height) + "\n";
}
void Rect::print()
{
	std::cout << "Position: [" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + "]\n";
}
int Rect::get_width() const { return width; }
int Rect::get_height() const { return height; }
Corners Rect::get_corners()
{
	return {x, y, x + width, y + height};
}
void Rect::setloc(int X, int Y)
{
	x = X;
	y = Y;
	located = true;
}
bool Rect::is_set() { return located; }
void Rect::set_false() { located = false; }
