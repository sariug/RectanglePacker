
#include <algorithm>
#include <cmath>
#include "PackNode.h"
#include "Plotter.h"
int main(int argc, char *argv[])
{
	std::string output = argv[2];
	if (!argv[1] || !argv[2] || (output != "m" && output != "csv"))
	{
		std::cout << "Please enter the correctly next time, example:" << std::endl;
		std::cout << "\t ./rectangle_packing /path/to/file.txt m" << std::endl;
		std::cout << "\t ./rectangle_packing /path/to/file.txt csv" << std::endl;
		exit(1);
	}
	RectLoader Loader(argv[1]);
	auto rectangles = Loader.load();

	// Sort rectangles by height
	std::sort(std::begin(rectangles), std::end(rectangles), [](const Rect &a, const Rect &b) -> bool { return a.get_height() > b.get_height(); });

	// Create an arbitrary Rectangular that we can fit all (for example sum of all heights)
	int sum_of_areas = 0;
	for (auto &r : rectangles)
		sum_of_areas += r.area();
	int edge = std::sqrt<int>(sum_of_areas);

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

	// Print output
	if (output == "m")
		Loader.print_for_matlab(rectangles);
	else if (output == "csv")
		Loader.print_to_csv(rectangles);
	
	// Plot output
	Plotter P(Head.w);
	for (auto &r : rectangles)
		P.add_rectangle({r.get_corners()[0], r.get_corners()[1], r.get_corners()[0] + r.get_width(), r.get_corners()[1] + r.get_height()});
	
	P.show();
	std::cout << "Smallest square that all the rectangles can fit is " << Head.w << " " << Head.h << std::endl;
	
	return 0;
}
