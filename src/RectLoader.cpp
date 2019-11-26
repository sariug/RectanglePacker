#include "RectLoader.h"

RectLoader::RectLoader(const std::string &filePath) : filepath(filePath) {}
std::vector<Rect>
RectLoader::load()
{
	std::vector<Rect> rects;
	std::ifstream file(filepath.c_str());
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a >> b))
		{
			break;
		}
		rects.push_back(Rect(a, b));
	}
	file.close();
	std::cout << "Loading rectangles are completed" << std::endl;
	return rects;
}
void RectLoader::print_for_matlab(std::vector<Rect> &rects)
{
	std::ofstream myfile;
	int counter = 1;
	myfile.open(filepath.substr(0, filepath.find(".txt")) + "_output.m");
	for (auto&r : rects)
	{
		myfile << r.print_matlab() << "text(" << std::to_string((r.get_corners()[0] + r.get_corners()[2]) / 2.0) << ", " << std::to_string((r.get_corners()[1] + r.get_corners()[3]) / 2.0)
			<< ", '" << std::to_string(counter) << "', 'FontSize', 14);\n";
		counter++;
	}

	myfile.close();
	std::cout << "Printing for MATLAB is completed." << std::endl;
}

void RectLoader::print_to_csv(std::vector<Rect> &rects)
{
	std::ofstream myfile;
	int counter = 1;
	myfile.open(filepath.substr(0, filepath.find(".txt")) + "_output.csv");
	for (auto&r : rects)
	{
		myfile << r.print_csv();
	}

	myfile.close();
	std::cout << "Printing for CSV is completed." << std::endl;
}

