#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "Cube.h"
#include "OBJObject.h"

class Rasterizer {

	void loadData();
	void clearBuffer();
	void drawPoint(int x, int y, float r, float g, float b);
	static void rasterize();
	void resizeCallback(GLFWwindow* window, int width, int height);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void displayCallback(GLFWwindow* window);
	void errorCallback(int error, const char* description);


};

#endif

