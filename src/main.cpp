#include <iostream>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "CA.hpp"

GLFWwindow* window;
Shader myShader;
CA GameOfLife;

int windowSquare = 1000;

int CellSize = 0;
float NxN = 0;
int N = 0;

uint32_t VAO;

std::vector<glm::vec2> VBO;
uint32_t VBOHandle = 0;

std::vector<uint32_t> IBO;
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

	NxN =  N * N;
	window = glfwCreateWindow(windowSquare, windowSquare, "Exercise 3", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, NULL);
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glViewport(0,0, windowSquare, windowSquare);

	myShader = Shader("assets/Shaders/shader.vs", "assets/Shaders/shader.fs");
	GameOfLife = CA(N);

	

	//set up the VBO

	for (int y = 0; y <= N; y++)
	{
		for (int x = 0; x <= N; x ++)
		{
			VBO.push_back(glm::vec2{ ((float)x - 2.0f)/(N - 2.0f),((float)y - 2.0f)/(N - 2.0f)});
		}
	}

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, VBOHandle);
	glBufferData(GL_ARRAY_BUFFER, VBO.size() * sizeof(glm::vec2), &VBO[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

	UpdateIBO();

	glGenBuffers(1, &IBOHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBO.size() * sizeof(uint32_t), &IBO[0], GL_DYNAMIC_DRAW);

	


}

void run()
{
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GameOfLife.NextGeneration();
		UpdateIBO();

		myShader.use();
		glDrawElements(GL_TRIANGLES, IBO.size(), GL_UNSIGNED_INT, nullptr);
		
		int x = glGetError();

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void UpdateIBO()
{
	uint32_t BLI = 0; //Bottom Left Index
	uint32_t IBOMax = N + 1;
	IBO.clear();
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (GameOfLife.grids[GameOfLife.currentGridIndex][x][y])
			{
				BLI = (y * (IBOMax)) + x; //this is the index of the bottom left vertice
				IBO.push_back(BLI);
				IBO.push_back(BLI + IBOMax + 1);
				IBO.push_back(BLI + 1); 
				
				IBO.push_back(BLI);
				IBO.push_back(BLI + IBOMax + 1);
				IBO.push_back(BLI + IBOMax);
			}
		}
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBO.size() * sizeof(uint32_t), &IBO[0], GL_DYNAMIC_DRAW);


}