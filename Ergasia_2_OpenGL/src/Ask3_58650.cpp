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

#include "Camera.h"
Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;
float previousMousePositonX = 400.0f;
float previousMousePositonY = 300.0f;

bool firstMouse = true;


void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);

	if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);



}

void MousPositionCallback(GLFWwindow* givenWindow, double givenMousePositionX, double givenMousePositionY)
{
	//std::cout << givenMousePositionX << std::endl;
	//std::cout << givenMousePositionY << std::endl;

	if (firstMouse)
	{
		previousMousePositonX = givenMousePositionX;
		previousMousePositonY = givenMousePositionY;

		firstMouse = false;
	}

	float offsetX = givenMousePositionX - previousMousePositonX;
	float offsetY = previousMousePositonY - givenMousePositionY;
	previousMousePositonX = givenMousePositionX;
	previousMousePositonY = givenMousePositionY;

	myCamera.ProcessMouseMovement(offsetX, offsetY);
}

void ScrollCallback(GLFWwindow* givenWindow, double givenScrollOffsetX, double givenScrollOffsetY)
{
	myCamera.ProcessMouseScroll(givenScrollOffsetY);
}




int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Askisi_3_Herculers_Gousis_AM:58650", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	

	glfwSetCursorPosCallback(window, MousPositionCallback);

	glfwSetScrollCallback(window, ScrollCallback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



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
		//position            //color             
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,

		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,

		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(3.0f,  0.0f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0f)
	 
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


	Shader shaderProgram("res/Shaders/VertexShader_13.txt", "res/Shaders/FragmentShader_13.txt");

	Shader shaderProgram1("res/Shaders/VertexShader_13.txt", "res/Shaders/FragmentShader_13.txt");

	Shader shaderProgram2("res/Shaders/VertexShader_13.txt", "res/Shaders/FragmentShader_13.txt");

	

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	bool animate = true;
	bool rotation1 = true;
	bool rotation2 = true;
	bool rotation3 = true;
	bool rotation4 = true;
	bool rotation5 = true;

	bool show_another_window = false;
	bool show_demo_window = true;
	float scale1;
	float scale2;
	float scale3;


	float rotate;
	// Game loop

	static float f2 = 1.0f;
	static float f2_saved = f2;

	static float f3 = 1.0f;
	static float f3_saved = f3;

	static float f4 = 1.0f;
	static float f4_saved = f4;

	static float f5 = 1.0f;
	static float f5_saved = f5;

	static float f6 = 1.0f;
	static float f6_saved = f6;

	static float rotation_angle1 = 0.0f;

	static float rotation_angle2 = 0.0f;

	static float rotation_angle3 = 0.0f;

	static float rotation_angle4 = 0.0f;

	static float rotation_angle5 = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		float time = glfwGetTime();
		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;


		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render Using the shader program
		shaderProgram.use();
		shaderProgram1.use();
		shaderProgram2.use();




		glm::mat4 view;
		view = glm::translate(identity, glm::vec3(-2.0f, -3.0f, -18.0f));
		//view = myCamera.GetViewMatrix();
		view = glm::rotate(view, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.3f, 100.0f);
		//projection = glm::ortho(-5.0f, 5.0f, -6.0f, 6.0f, -15.0f, 18.0f);
		int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Begin("Tools");
		ImGui::Checkbox("animate", &animate);
		
		static float f = 2.0f;
		ImGui::SliderFloat("radius12", &f, 2.0f, 3.0f);
		static float f1 = 0.0f;
		
		ImGui::SliderFloat("radius13", &f1, 0.0f, 1.5f);
		

		
		ImGui::SliderFloat("speed1", &f2_saved, 1.0f, 30.0f);
		ImGui::SameLine();
		ImGui::Checkbox("rotation1", &rotation1);

		
		ImGui::SliderFloat("speed2", &f3_saved, 1.0f, 30.0f);
		ImGui::SameLine();
		ImGui::Checkbox("rotation2", &rotation2);

		
		ImGui::SliderFloat("speed3", &f4_saved, 1.0f, 30.0f);
		ImGui::SameLine();
		ImGui::Checkbox("rotation3", &rotation3);

		
		ImGui::SliderFloat("speed4", &f5_saved, 1.0f, 30.0f);

		ImGui::SameLine();
		ImGui::Checkbox("rotation4", &rotation4);

		
		ImGui::SliderFloat("speed5", &f6_saved, 1.0f, 30.0f);

		ImGui::SameLine();
		ImGui::Checkbox("rotation5", &rotation5);
		

		if (rotation1)
		{
			f2 = f2_saved;
			rotation_angle1 += f2 * deltaTime *60.0f;
		}


		if (rotation2)
		{
			f3 = f3_saved;
			rotation_angle2 += f3* deltaTime * 60.0f;
		}

		if (rotation3)
		{
			f4 = f4_saved;
			rotation_angle3 += f4 * deltaTime *60.0f;
		}

		if (rotation4)
		{
			f5 = f5_saved;
			rotation_angle4 += f5 * deltaTime * 60.0f;
		}

		if (rotation5)
		{
			f6 = f6_saved;
			rotation_angle5 += f6 * deltaTime * 60.0f;
		}


		glm::vec3 rotaionAxis;
		glm::mat4 mami(1.0f);
		glm::mat4 pasxa(1.0f);
		glm::mat4 model;
		scale1 = 1.6;
		rotaionAxis = glm::vec3(0.0f, 1.0f, 0.0f);

		model = glm::translate(identity, cubePositions[0]);
		model = glm::scale(model, glm::vec3(scale1, scale1, scale1));
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation_angle1), rotaionAxis);
		int model1 = glGetUniformLocation(shaderProgram.ID, "model");

		glUniformMatrix4fv(model1, 1, GL_FALSE, &model[0][0]);
		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami1 = glGetUniformLocation(shaderProgram.ID, "mami");
		glUniformMatrix4fv(mami1, 1, GL_FALSE, &mami[0][0]);

		pasxa = glm::rotate(pasxa, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		int pasxa0 = glGetUniformLocation(shaderProgram.ID, "pasxa");
		glUniformMatrix4fv(pasxa0, 1, GL_FALSE, &pasxa[0][0]);


		glDrawArrays(GL_TRIANGLES, 0, 36);

//...........................................................................
		glm::vec3 rotaionAxis3;
		
		scale2 = 1.5;
		model = glm::translate(identity, cubePositions[1]);
		model = glm::scale(model, glm::vec3(scale2, scale2, scale2));
		model = glm::translate(model, glm::vec3(f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation_angle2), rotaionAxis);
		int model2 = glGetUniformLocation(shaderProgram1.ID, "model");
		glUniformMatrix4fv(model2, 1, GL_FALSE, &model[0][0]);

		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami2 = glGetUniformLocation(shaderProgram1.ID, "mami");
		glUniformMatrix4fv(mami2, 1, GL_FALSE, &mami[0][0]);

		rotaionAxis3 = glm::vec3( mami2, 1.0f, 0.0f);
		pasxa = glm::rotate(pasxa, glm::radians(rotation_angle4), rotaionAxis3);

		int pasxa1 = glGetUniformLocation(shaderProgram1.ID, "pasxa");
		glUniformMatrix4fv(pasxa1, 1, GL_FALSE, &pasxa[0][0]);
		

		glDrawArrays(GL_TRIANGLES, 0, 36);

//..............................................................

		glm::vec3 rotaionAxis2;
		
		scale3 = 1.0;
		model = glm::translate(identity, cubePositions[2]);
		model = glm::scale(model, glm::vec3(scale3, scale3, scale3));
		model = glm::translate(model, glm::vec3(f1+f, 0.0f,0.0f));
		model = glm::rotate(model, glm::radians(rotation_angle3), rotaionAxis);
		int model3 = glGetUniformLocation(shaderProgram2.ID, "model");
		glUniformMatrix4fv(model3, 1, GL_FALSE, &model[0][0]);

		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami3 = glGetUniformLocation(shaderProgram2.ID, "mami");
		glUniformMatrix4fv(mami3, 1, GL_FALSE, &mami[0][0]);
		
		rotaionAxis2 = glm::vec3(0.0f, 1.0f, 0.0f);
		pasxa = glm::translate(pasxa, glm::vec3(f+f1+4.0f, 0.0f, 0.0f));
		pasxa = glm::rotate(pasxa, glm::radians(rotation_angle5), rotaionAxis2);

		int pasxa2 = glGetUniformLocation(shaderProgram2.ID, "pasxa");
		glUniformMatrix4fv(pasxa2, 1, GL_FALSE, &pasxa[0][0]);


		glDrawArrays(GL_TRIANGLES, 0, 36);

//.........................................................................
		
		
		


		if (!rotation1)
		{
			rotation_angle1 += f2 * deltaTime * 60.0f;
			f2 = 0;
			
		}
		else {
			f2 = f2_saved;
			
		}



		if (!rotation2)
		{
			rotation_angle2 += f3 * deltaTime * 60.0f;
			f3 = 0;
			
		}
		else {

			f3 = f3_saved;
		}


		if (!rotation3)
		{
			rotation_angle3 += f4 * deltaTime * 60.0f;
			f4 = 0;
			
		}
		else {
			f4= f4_saved;

		}

		if (!rotation4)
		{
			rotation_angle4 += f5 * deltaTime * 60.0f;
			f5= 0;
			
		}
		else {
			f5 = f5_saved;

		}

		if (!rotation5)
		{
			rotation_angle5 += f6 * deltaTime * 60.0f;
			f6 = 0;
			
		}
		else {
			f6 = f6_saved;

		}

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