#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

GLFWwindow* window;

const int CellSize = 10;
int N = 0;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


void init();
void run();

int main()
{
	std::cout << " Enter the grids length (NxN)\nN: ";
	std::cin >> N;
	
	init();
	run();
	
	glfwTerminate();
	return 0;
}

void init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	if (!glfwInit())
		return;

	int NxN = CellSize * N;
	window = glfwCreateWindow(NxN, NxN, "Exercise 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, NULL);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, NxN, NxN);

}

void run()
{
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}