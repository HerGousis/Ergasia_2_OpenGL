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

#define 	GLFW_KEY_W   87


void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}

bool flag = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (flag) {
			flag = !flag;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glLineWidth(10.0f);

		}
		else {
			flag = !flag;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glLineWidth(10.0f);

		}
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Askisi_1_Herculers_Gousis_AM:58650", NULL, NULL);

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
	glfwSetKeyCallback(window, key_callback);
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
	  glm::vec3(1.5f,  0.0f,  0.0f),//1
	  glm::vec3(1.67f,  0.15f, 0.0f),//2
	  glm::vec3(1.6f, 0.35f, 0.0f),//3
	 glm::vec3(1.4f, 0.35f, 0.0f),//4
	  glm::vec3(1.33f, 0.15f, 0.0f),//5
	  glm::vec3(-0.69f,  0.0f, 0.0f),//1
	  glm::vec3(-0.6f, 0.42f, 0.0f),//2
	  glm::vec3(-0.86f,  0.75f, 0.0f),//3
	  glm::vec3(-1.29f,  0.75f, 0.0f),//4
	 glm::vec3(-1.55f,  0.42f, 0.0f),//5
	 glm::vec3(-1.45f,  0.0f, 0.0f),//6
	 glm::vec3(-1.07f,  -0.19f, 0.0f),//7


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


	Shader shaderProgram("res/Shaders/VertexShader_11.txt", "res/Shaders/FragmentShader_11.txt");

	Shader shaderProgram1("res/Shaders/VertexShader_11.txt", "res/Shaders/FragmentShader_11.txt");

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
		shaderProgram1.use();

		glm::mat4 view;
		view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -3.0f));
		int viewLocation = glGetUniformLocation( shaderProgram1.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


		glm::mat4 projection;
		projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.3f, 100.0f);
		int projectionLocation = glGetUniformLocation( shaderProgram1.ID, "projection");
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
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Begin("Tools");
		ImGui::Checkbox("animate", &animate);
		static float R = 0.0f;
		ImGui::SliderFloat("R", &R, 0.0f, 1.0f);

		static float G = 0.0f;
		ImGui::SliderFloat("G", &G, 0.0f, 1.0f);

		static float B = 0.0f;
		ImGui::SliderFloat("B", &B, 0.0f, 1.0f);

		static float R1 = 1.0f;
		ImGui::SliderFloat("R1", &R1, 0.0f, 1.0f);

		static float G1 = 0.0f;
		ImGui::SliderFloat("G1", &G1, 0.0f, 1.0f);


		static float B1 = 0.0f;
		ImGui::SliderFloat("B1", &B1, 0.0f, 1.0f);

		glm::vec3 color1;

		int uniformLocation = glGetUniformLocation(shaderProgram.ID, "color1");
		glUniform3f(uniformLocation, R1, G1, B1);
		

		int a;
		a = 1;
		for (int i = 5; i < 12; i++)
		{
			
			glm::mat4 model;
			model = glm::translate(identity, cubePositions[i]);
			model = glm::rotate(model, glm::radians(51.4f) * a, glm::vec3(0.0f, 0.0f, 1.0f));
			int modelLocation1 = glGetUniformLocation(shaderProgram1.ID, "model");
			glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, &model[0][0]);
			
			glDrawArrays(GL_POLYGON, 0, 7);
			a = a + 1;

		}

		int uniformLocation1 = glGetUniformLocation(shaderProgram1.ID, "color1");

		glUniform3f(uniformLocation1, R, G, B);
		glDrawArrays(GL_POLYGON, 0, 7);
		


		ImGui::End();

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}