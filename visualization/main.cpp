
#include "Plotter.h"

const float toRadians = glm::pi<float>() / 180.0f;
GLfloat deltaTime =.0f;
GLfloat lastTime = .0f;


int main()
{
	Plotter P;
	P.add_rectangle({2,3,7,10});
	P.show();

	// Loop until it is closed

	return 0;
}