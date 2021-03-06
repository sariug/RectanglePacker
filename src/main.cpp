
#include <algorithm>
#include <cmath>
#include <filesystem> 
#include <numeric>
#include <execution>
#include "PackNode.h"
#include "Plotter.h"
void PlotResults(int edge, std::vector<Rect> rectangles);
int main(int argc, char *argv[])
{
	std::string output = argv[2] ? argv[2] : "";

	if (!std::filesystem::exists(argv[1]) || (output != "m" && output != "csv"))
	{
		std::cout << "Please enter the correctly next time, example:\n"
		<< "\t ./rectangle_packing /path/to/file.txt m\n" 
		<< "\t ./rectangle_packing /path/to/file.txt csv\n";
		exit(1);
	}
	RectLoader Loader(argv[1]);
	auto rectangles = Loader.load();

	// Sort rectangles by height
	std::sort(std::begin(rectangles), std::end(rectangles), [](const Rect &a, const Rect &b) -> bool { return a.get_height() > b.get_height(); });

	// Create an arbitrary Rectangular that we can fit all (for example sum of all heights)
	int edge = std::sqrt<int>(std::accumulate(rectangles.begin(), rectangles.end(), 0,
											  [](auto SUM, auto r) { return SUM + r.area(); }));
											  
	PackNode Head(0, 0, edge, edge);

	std::cout << "Starting Square : " << Head.w << " " << Head.h << std::endl;

	for (auto &r : rectangles)
	{
		Head.insert(r);
		while (!r.is_set())
		{
			Head.extend(edge);
			edge++;
			Head.insert(r);
		}
	}

	// Print result
	output == "m" ? Loader.print_for_matlab(rectangles) : (output == "csv" ? Loader.print_to_csv(rectangles) : throw "Wrong output type !");
    
	//Plot Results;
	PlotResults(Head.w, rectangles);

	std::cout << "Smallest square that all the rectangles can fit is " << Head.w << " " << Head.h << std::endl;

	return 0;
}
void PlotResults(int edge, std::vector<Rect> rectangles)
{
	// Plot output
	Plotter P(edge);
	for (auto &r : rectangles)
		P.add_rectangle({r.get_corners()[0], r.get_corners()[1], r.get_corners()[0] + r.get_width(), r.get_corners()[1] + r.get_height()});
	P.show();
}