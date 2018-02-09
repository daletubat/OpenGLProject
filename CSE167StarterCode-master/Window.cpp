#include "Window.h"
#include "Rasterizer.h"

const char* window_title = "GLFW Starter Project";
Cube cube(5.0f);


OBJObject* currObj;
OBJObject bunny("C:\\Users\\Dale\\Documents\\_Schoolwork\\Year 4\\Fall 2016\\CSE 167 - Computer Graphics\\Project 1\\Take 2\\CSE167StarterCode-master\\CSE167StarterCode-master\\bunny.obj");
OBJObject dragon("C:\\Users\\Dale\\Documents\\_Schoolwork\\Year 4\\Fall 2016\\CSE 167 - Computer Graphics\\Project 1\\Take 2\\CSE167StarterCode-master\\CSE167StarterCode-master\\dragon.obj");
OBJObject bear("C:\\Users\\Dale\\Documents\\_Schoolwork\\Year 4\\Fall 2016\\CSE 167 - Computer Graphics\\Project 1\\Take 2\\CSE167StarterCode-master\\CSE167StarterCode-master\\bear.obj");


int Window::width;
int Window::height;
int ptSize = 1;

void Window::initialize_objects()
{
	currObj = &bunny;
}

void Window::clean_up()
{
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

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

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);
	// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective of the projection viewing frustum
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0);
	// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -20);
}

void Window::idle_callback()
{
	// Perform any updates as necessary. Here, we will spin the cube slightly.
	currObj->update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();
	
	// Render objects
	currObj->draw();

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
		//CHANGE MODEL//
		else if (key == GLFW_KEY_F1)
		{
			currObj = &bunny;
		}
		else if (key == GLFW_KEY_F2)
		{
			currObj = &dragon;
		}
		else if (key == GLFW_KEY_F3)
		{
			currObj = &bear;
		}
		///////////////

		//MODIFY MODEL//
		//need to use glm::mat4(1.0f)
		//OBJObject::toWorld
		
		//PixelSize
		else if (key == GLFW_KEY_P) {
			if (mods == GLFW_MOD_SHIFT) //P - pixel size bigger
			{
				ptSize++;
				glPointSize(ptSize);
			}
			else {
				if (ptSize > 1) {
					ptSize--;
					glPointSize(ptSize);
				}
			}
		}

		//X Translation
		else if (key == GLFW_KEY_X) {
			if (mods == GLFW_MOD_SHIFT) 
			{
				currObj->tranX++;
			}
			else {
				currObj->tranX--;
			}

		}

		//Y Translation
		else if (key == GLFW_KEY_Y) {
			if (mods == GLFW_MOD_SHIFT)
			{
				currObj->tranY++;
			}
			else {
				currObj->tranY--;
			}
		}

		//Z Translation
		else if (key == GLFW_KEY_Z) {
			if (mods == GLFW_MOD_SHIFT)
			{
				currObj->tranZ++;
			}
			else {
				currObj->tranZ--;
			}

		}

		//Scale
		else if (key == GLFW_KEY_S) {
			if (mods == GLFW_MOD_SHIFT)
			{
				currObj->scale++;
			}
			else {
				if(currObj->scale > 1){
					currObj->scale--;
				}
			}
		}


		//Orbit
		else if (key == GLFW_KEY_O) {
			currObj->orbit++;
		}
		///////////////

		//Rasterizer Mode
		else if (key == GLFW_KEY_M) {
			Rasterizer::rasterize();
		}

	}
}
