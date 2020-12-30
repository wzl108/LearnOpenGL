#ifndef OPENGL_H
#define OPENGL_H


#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>


class OpenGL
{
	const int SCR_WIDTH = 360;
	const int SCR_HEIGHT = 180;

	GLFWwindow* window;

public:
	void processInput(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void initialize();
	void start();
	void exit();
};

#endif // !OPENGL_DEF