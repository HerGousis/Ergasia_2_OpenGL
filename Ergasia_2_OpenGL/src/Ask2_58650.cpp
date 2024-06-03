//58650 mod 6 =0
//U=0

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 1.0f;
bool direction1 = true;
float triOffset1 = 0.0f;
float triMaxOffset1 = 1.0f;
float triIncrement1 = 0.0005f;
float triIncrement = 0.0005f;



void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}




void ProcessInput(GLFWwindow* givenWindow) {

	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);

	if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS) {
			if (direction)
			{
				triOffset -= triIncrement;
			}
	}

	if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS) {
		if (direction)
		{
			triOffset += triIncrement;
		}
	}


	if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS) {
		if (direction1)
		{
			triOffset1 += triIncrement1;
		}
	}

	if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS) {
		if (direction1)
		{
			triOffset1 -= triIncrement1;
		}
	}

	if (triOffset1 >= triMaxOffset1)
	{
		triOffset1 = 1.0;

	}

	if (triOffset1 <= -triMaxOffset1)
	{
		triOffset1 = -1.0;

	}

	if (triOffset >= triMaxOffset)
	{
		triOffset = 1.0;

	}


	if (triOffset <= -triMaxOffset)
	{
		triOffset = -1.0;

	}

}








int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Askisi_2_Herculers_Gousis_AM:58650", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	const char* glsl_version = "#version 330";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//Data


	GLfloat vertices[] = {

		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f , 0.0f, 0.0f, 0.0f

	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),//1
	  glm::vec3(0.17f,  0.15f, 0.0f),//2
	  glm::vec3(0.1f, 0.35f, 0.0f),//3
	 glm::vec3(-0.1f, 0.35f, 0.0f),//4
	  glm::vec3(-0.17f, 0.15f, 0.0f),//5
	  
	};
	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Shader shaderProgram("res/Shaders/VertexShader_12.txt", "res/Shaders/FragmentShader_12.txt");

	

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	bool animate = true;
	bool show_another_window = false;
	bool show_demo_window = true;
	float scale;




	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		float time = glfwGetTime();

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Using the shader program
		shaderProgram.use();
		

		glm::mat4 view;
		view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -2.0f));
		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


		glm::mat4 projection;
		projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.3f, 100.0f);
		int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


		for (int i = 0; i < 5; i++)
		{
			glm::mat4 model;
			

			model = glm::translate(identity, cubePositions[i]);
			model = glm::rotate(model, glm::radians(72.0f) * i, glm::vec3(0.0f, 0.0f, 1.0f));
			int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
			glDrawArrays(GL_POLYGON, 0, 5);

		}
		
		
		

		glm::mat4 model1(1.0f);
		model1 = glm::translate(model1, glm::vec3(triOffset, triOffset1, 0.0f));

		int modelLocation1 = glGetUniformLocation(shaderProgram.ID, "model1");
		glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, &model1[0][0]);
		
		glm::vec3 color1;

		int uniformLocation = glGetUniformLocation(shaderProgram.ID, "color1");
		glUniform3f(uniformLocation, triOffset, triOffset1, 0);



		

		
	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}