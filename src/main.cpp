#include <iostream>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include "Shader.h"
#include "CA.hpp"

GLFWwindow* window;
Shader myShader;
CA GameOfLife;

const int CellSize = 10;
int NxN = 0;
int N = 0;


std::vector<glm::ivec2> VBO;
uint32_t VBOHandle = 0;

std::vector<int> IBO;
uint32_t IBOHandle = 0;

void init();
void run();

void UpdateIBO();


int main()
{
	std::cout << " Enter the cell amount\nN: ";
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

	NxN = CellSize * N;
	window = glfwCreateWindow(NxN, NxN, "Exercise 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, NULL);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	myShader = Shader("assets/Shaders/shader.vs", "assets/Shaders/shader.fs");
	GameOfLife = CA(N);

	glViewport(0, 0, NxN, NxN);

	//set up the VBO

	for (int y = 0; y <= NxN; y += CellSize)
	{
		for (int x = 0; x <= NxN; x += CellSize)
		{
			VBO.push_back(glm::ivec2{ x,y });
		}
	}

	glGenBuffers(1, &VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, VBOHandle);
	glBufferData(GL_ARRAY_BUFFER, VBO.size(), &VBO[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(int), (void*)0);

	myShader.use();


}

void run()
{
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		UpdateIBO();

		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void UpdateIBO()
{
	int BLI = 0; //Bottom Left Index
	int IBOMax = N + 1;
	IBO.clear();
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (GameOfLife.grid[x][y])
			{
				BLI = (y * (IBOMax)) + x; //this is the index of the bottom left vertice
				IBO.push_back(BLI);
				IBO.push_back(BLI + 1);
				IBO.push_back(BLI + IBOMax);
				IBO.push_back(BLI + IBOMax + 1);
			}
		}
	}
}