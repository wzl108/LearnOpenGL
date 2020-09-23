#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <../Test/LearnOpenGLTest2/LearnOpenGLTest2/Shader.h>
using namespace std;


int shaderProgram;
GLFWwindow* window;
unsigned int VAO;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void buidAndCompilerShader();
int OpenGLInit();
void MainLoop();
void VertexConfig();

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";




int main()
{
	
	OpenGLInit();
	

	//������������
	VertexConfig();
	
	//������Ⱦ��ѭ��
	MainLoop();

	//��Դ�ͷ�
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void MainLoop()
{

	Shader ourShader("../Shaders/TestShader.vs", "../Shaders/TestShader.ts");


	//������Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����ɫ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//��ⰴ��
		processInput(window);

		//�����ͱ�����ɫ��
		buidAndCompilerShader();

		// 2. ��������Ⱦһ������ʱҪʹ����ɫ������
		//glUseProgram(shaderProgram);
		ourShader.use();
		
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		ourShader.setFloat("testColor", greenValue);

		// ����uniform��ɫ
		/*float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/


		glBindVertexArray(VAO);
		// 3. ��������
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);

	}
}


void VertexConfig()
{
	// ��������
	float vertices[] = {
	-0.5f, 0.0f, 0.0f,
	 0.0f, -0.0f, 0.0f,
	 -0.25f,  0.25f, 0.0f,

	 0.5f, 0.0f, 0.0f,
	 0.0f, 0.0f, 0.0f,
	 0.25f,  0.25f, 0.0f,
	};

	//���㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//�����������
	//unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// 0. ���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void buidAndCompilerShader()
{
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

int OpenGLInit()
{
	// glfw����      Tips: glfw����������OpenGL content�Ŀ�
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//�������ڶ���
	window = glfwCreateWindow(640, 360, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//��ʼ��glad      Tips: gladʹOpenGL�ĺ������ü�
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�����ӿ�
	glViewport(0, 0, 640, 360);
	//ע�ᴰ�ڴ�С�任ʱ�Ļص�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



}

