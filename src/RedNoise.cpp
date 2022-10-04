#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

#define WIDTH 320
#define HEIGHT 240

// using namespace std;

std::vector<float> interpolateSingleFloats(float from, float to, size_t numberOfValues)
{
	std::vector<float> resultSingle;
	float d = (to - from) / float(numberOfValues - 1);
	for (size_t i = 0; i < numberOfValues; i++)
		resultSingle.push_back(from + i * d);
	return resultSingle;
}

std::vector<glm::vec3> interpolateThreeElementValues(glm::vec3 from, glm::vec3 to, size_t numberOfValues)
{
	std::vector<glm::vec3> resultThree;
	glm::vec3 d = (to - from) / glm::vec3(numberOfValues - 1);
	for (size_t i = 0; i < numberOfValues; i++)
		resultThree.push_back(from + (glm::vec3(i)) * d);
	return resultThree;
}

void draw(DrawingWindow &window)
{
	window.clearPixels();
	std::vector<float> resultSingle;
	resultSingle = interpolateSingleFloats(0, 255, window.width);
	for (size_t y = 0; y < window.height; y++)
	{
		for (size_t x = 0; x < window.width; x++)
		{
			float red = resultSingle[(window.width - 1) - x];
			float green = resultSingle[(window.width - 1) - x];
			float blue = resultSingle[(window.width - 1) - x];
			uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
			window.setPixelColour(x, y, colour);
		}
	}
	std::vector<glm::vec3> leftHandSide;
	leftHandSide = interpolateThreeElementValues(glm::vec3(255, 0, 0), glm::vec3(255, 255, 0), window.height);
	std::vector<glm::vec3> rightHandSide;
	rightHandSide = interpolateThreeElementValues(glm::vec3(0, 0, 255), glm::vec3(0, 255, 0), window.height);
	std::vector<glm::vec3> colouredImage;
	for (size_t y = 0; y < window.height; y++)
	{
		colouredImage = interpolateThreeElementValues(leftHandSide[y], rightHandSide[y], window.width);
		for (size_t x = 0; x < window.width; x++)
		{
			uint32_t finalColour = (255 << 24) + (int(colouredImage[x].x) << 16) + (int(colouredImage[x].y) << 8) + int(colouredImage[x].z);
			window.setPixelColour(x, y, finalColour);
		}
	}
}

void handleEvent(SDL_Event event, DrawingWindow &window)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_LEFT)
			std::cout << "LEFT" << std::endl;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			std::cout << "RIGHT" << std::endl;
		else if (event.key.keysym.sym == SDLK_UP)
			std::cout << "UP" << std::endl;
		else if (event.key.keysym.sym == SDLK_DOWN)
			std::cout << "DOWN" << std::endl;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		window.savePPM("output.ppm");
		window.saveBMP("output.bmp");
	}
}

int main(int argc, char *argv[])
{
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event;
	while (true)
	{
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event))
			handleEvent(event, window);
		draw(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
		std::vector<float> resultSingle;
		resultSingle = interpolateSingleFloats(2.2, 8.5, 7);
		for (size_t i = 0; i < resultSingle.size(); i++)
			std::cout << resultSingle[i] << " ";
		std::cout << std::endl;
		std::vector<glm::vec3> resultThree;
		resultThree = interpolateThreeElementValues(glm::vec3(1.0, 4.0, 9.2), glm::vec3(4.0, 1.0, 9.8), 4);
		for (size_t i = 0; i < resultThree.size(); i++)
			std::cout << resultThree[i].x << " "
					  << " " << resultThree[i].y << " " << resultThree[i].z << std::endl;
		std::cout << std::endl;
	}
}
