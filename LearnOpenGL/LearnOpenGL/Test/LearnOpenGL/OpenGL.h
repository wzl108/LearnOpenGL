#ifndef OPENGL_DEF
#define OPENGL_DEF


#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>


class OpenGL
{
	const int WIDTH = 360;
	const int HEIGHT = 180;

	GLFWwindow* window;

public:
	void processInput(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void initialize();
	void start();
	void exit();
};

#endif // !OPENGL_DEF