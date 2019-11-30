#pragma once
#include "Rect.h"

Rect::Rect() noexcept {};
Rect::Rect(int w, int h) noexcept : width(w), height(h), x(0), y(0) {}
Rect::Rect(int X, int Y, int W, int H) noexcept : x(X), y(Y), width(W), height(H) {}

int Rect::area() const { return width * height; }
std::string Rect::print_matlab()
{
	return "rectangle('Position', [" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + "]);\n";
}
std::string Rect::print_csv()
{
	return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(x + width) + ", " + std::to_string(y + height) + "\n";
}

std::ostream & operator << (std::ostream &out, const Rect &r)
{
out	<< "Position: [" + std::to_string(r.x) + " " + std::to_string(r.y) + " " + std::to_string(r.width) + " " + std::to_string(r.height) + "]\n";
	return out;
}

int Rect::get_width() const { return width; }
int Rect::get_height() const { return height; }
std::vector<int> Rect::get_corners()
{
	return {x, y, x + width, y + height};
}
void Rect::setloc(const int &X, const int &Y)
{
	x = X;
	y = Y;
	located = true;
}
bool Rect::is_set() { return located; }
void Rect::set_false() { located = false; }
