
#include "Rasterizer.h"
#include <glm/gtc/type_ptr.hpp>

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];

using namespace std;

OBJObject* currObj2;
OBJObject bunny2("C:\\Users\\Dale\\Documents\\_Schoolwork\\Year 4\\Fall 2016\\CSE 167 - Computer Graphics\\Project 1\\Take 2\\CSE167StarterCode-master\\CSE167StarterCode-master\\bunny.obj");
OBJObject dragon2("C:\\Users\\Dale\\Documents\\_Schoolwork\\Year 4\\Fall 2016\\CSE 167 - Computer Graphics\\Project 1\\Take 2\\CSE167StarterCode-master\\CSE167StarterCode-master\\dragon.obj");
OBJObject bear2("C:\\Users\\Dale\\Documents\\_Schoolwork\\Year 4\\Fall 2016\\CSE 167 - Computer Graphics\\Project 1\\Take 2\\CSE167StarterCode-master\\CSE167StarterCode-master\\bear.obj");

struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};

void loadData()
{
	// point cloud parser goes here
}

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = { 0.0, 1.0, 0.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
	}
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y*window_width * 3 + x * 3;
	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}



void rasterize()
{
	
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it

	//MATH//
	//p' = D * C-1 * P * M * p

	glm::mat4 M = currObj2->get2w(); //model matrix
	glm::mat4 C = glm::lookAt(glm::vec3(0, 0, -20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); //Camera Matrix
	glm::mat4 P = glm::perspective(glm::radians(60.0f), (float)window_width / (float)window_height, 1.0f, 1000.0f); //not sure what goes in here yet
	
	//creation of D
	float x0, y0 = 0;
	float x1 = window_width;
	float y1 = window_height;

	float toD[16] = 
	{ (x1 - x0) / 2, 0, 0, 0,
		0, (y1 - y0) / 2, 0, 0,
		0, 0, 1.0f / 2.0f, 0,
		(x0 + x1) / 2, (y0 + y1) / 2, 1.0f / 2.0f, 1.0f };
	glm::mat4 D = glm::make_mat4(toD);

	//acquire p, does math
	for (int i = 0; i < currObj2->getVert().size(); i++) {
		glm::vec3 top = currObj2->getVert()[i]; //grabs vertex
		glm::vec3 col = currObj2->getNorm()[i]; //grabs color value
		glm::vec4 p = glm::vec4(top.x, top.y, top.z, 1); //turns vertex into homogenous vector

		glm::vec4 p_prime = D * C * P * M * p; 

		drawPoint(p_prime.x, p_prime.y, col.r, col.g, col.b);

	}



}

// Called whenever the window size changes
void resizeCallback(GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS  || action == GLFW_REPEAT)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void displayCallback(GLFWwindow* window)
{
	clearBuffer();
	rasterize();

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void errorCallback(int error, const char* description)
{
	// Print error
	fputs(description, stderr);
}
/*
int main(int argc, char** argv) {
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(window_height, window_height, "Rastizer", NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	loadData();

	// Set the error callback
	glfwSetErrorCallback(errorCallback);
	// Set the key callback
	glfwSetKeyCallback(window, keyCallback);
	// Set the window resize callback
	glfwSetWindowSizeCallback(window, resizeCallback);

	// Loop while GLFW window should stay open
	while (!glfwWindowShouldClose(window))
	{
		// Main render display callback. Rendering of objects is done here.
		displayCallback(window);
	}

	// Destroy the window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
*/

