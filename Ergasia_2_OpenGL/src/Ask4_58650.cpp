#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader_58650_21.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera_58650_21.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



//#define 	GLFW_KEY_LEFT_CONTROL   341
#define 	GLFW_KEY_LEFT_SHIFT   340
Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f)); // dhmioyrgia kamera kai thesi

float deltaTime = 0.0f; //gia na mhn epirazei h karta grafikvn 
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;

float previousMousePositonX = 400.0f; // thesi pontiki
float previousMousePositonY = 300.0f;//thrsi pontiki

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
		myCamera.ProcessKeyboard(RIGHT, deltaTime );

	if (glfwGetKey(givenWindow, GLFW_KEY_E) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_Q) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		myCamera.MovementSpeed = 5000.0f * deltaTime;
	}
	else {
		myCamera.MovementSpeed = SPEED;
	}





}// metakinisi viewport alla einai to idio me thn metakinhsh toy antikimenoy 

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

void MousPositionCallback1(GLFWwindow* givenWindow, double givenMousePositionX, double givenMousePositionY)
{
	//std::cout << givenMousePositionX << std::endl;
	//std::cout << givenMousePositionY << std::endl;

	
}


void ScrollCallback(GLFWwindow* givenWindow, double givenScrollOffsetX, double givenScrollOffsetY)
{
	
		myCamera.ProcessMouseScroll(givenScrollOffsetY);
	
}
void ScrollCallback1(GLFWwindow* givenWindow, double givenScrollOffsetX, double givenScrollOffsetY)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{
	
			

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
			glfwSetCursorPosCallback(window, MousPositionCallback1);
			glfwSetScrollCallback(window, ScrollCallback1);
		

	}
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
	{
	
			
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
			glfwSetCursorPosCallback(window, MousPositionCallback);
		    glfwSetScrollCallback(window, ScrollCallback);	
		
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Askisi_4_Herculers_Gousis_AM:58650", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	//glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	// Set the callback function



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

	//--Vertex Data
	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // synistoses toy kathetoy dianismatos 0.0f,  0.0f, -1.0f
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,


		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 material_ambientColor[] =
	{
		  glm::vec3(0.0215f, 0.1745f, 0.0215f), //1
		  glm::vec3(0.135f, 0.2225f, 0.1575f), //2
		  glm::vec3(0.05375f, 0.05f, 0.06625f),//3
		  glm::vec3(0.1f, 0.18725f, 0.1745f),//4
		  glm::vec3(0.1745f, 0.01175f, 0.01175f),//5
		  glm::vec3(0.2125f, 0.1275f, 0.054f),//6
		  glm::vec3(0.24725f,	0.1995f,	0.0745f),//7
		  glm::vec3(0.0f,	0.0f,	0.0f),//8
		  glm::vec3(0.0f,	0.0f	,0.0f),//9
		  glm::vec3(0.0f,	0.0f,	0.0f),//10

	};

	glm::vec3 material_diffuseColor[] = {
		  glm::vec3(0.07568f, 0.61424f, 0.07568f), //1
		  glm::vec3(0.54f, 0.89f, 0.63f), //2
		  glm::vec3(0.18275f, 0.17f, 0.22525f),//3
		  glm::vec3(0.396f, 0.74151f, 0.69102f),//4
		  glm::vec3(0.61424f, 0.04136f, 0.04136f),//5
		  glm::vec3(0.714f, 0.4284f, 0.18144f),//6
		  glm::vec3(0.75164f,	0.60648f,	0.22648f),//7
		  glm::vec3(0.1f,	0.35f,	0.1f),//8
		  glm::vec3(0.5f,	0.0f	,0.0f),//9
		  glm::vec3(0.55f,	0.55f,	0.55f)//10

	};

	glm::vec3 material_specularColor[] = {
	      glm::vec3(0.633f, 0.727811f, 0.633f), //1
		  glm::vec3(0.316228f, 0.3168228f, 0.3168228f), //2
		  glm::vec3(0.332741f, 0.328634f, 0.346435f),//3
		  glm::vec3(0.297254f, 0.30829f, 0.306678f),//4
		  glm::vec3(0.727811f, 0.626959f, 0.626959f),//5
		  glm::vec3(0.393548f,0.271906f,0.166721f),//6
		  glm::vec3(0.628281f, 0.555802f, 0.366065f),//7
		  glm::vec3(0.50f,	0.50f,	0.50f),//8
		  glm::vec3(0.7f,	0.6f	,0.6f),//9
		  glm::vec3(0.70f,	0.70f,	0.70f),//10

	};

	float material_shininess[] = {

		float(0.6f), //1
	    float(0.1f), //2
		float(0.3f),//3
		float(0.1f),//4
		float(0.6f),//5
		float(0.2f),//6
		float(0.4f),//7
		float(0.25f),//8
		float(0.25f),//9
		float(0.25f)//10

		//float(0.4f),
		//float(0.4f),
        //float(0.4f),
        //float(0.4f),
        //float(0.4f),
		//float(0.4f),
        //float(0.4f),
        //float(0.4f),
        //float(0.4f),
        //float(0.4f)
	};

	glm::vec3 lightSourcePosition[]
	{
	glm::vec3 (2.3f, -3.3f, -4.0f),
	glm::vec3 (-3.0f, 1.0f, -10.0f),
	glm::vec3 (0.0f, 0.0f, -3.0f),

	glm::vec3 (0.0f, 10.0f, -10.0f),
	glm::vec3 (-10.0f, 10.0f, -10.0f),

	glm::vec3(5.0f, 5.0f, 5.0f)
	};



	glm::vec3 lightSourceDirection[]
	{
		glm::vec3(0.0f, -1.0f, 0.0f), // only for directional light
		glm::vec3(1.0f, -1.0f, 0.0f)
	};



	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//pername tis syntetagmenes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Shader shaderProgram("res/Shaders/VertexShader_21.txt", "res/Shaders/FragmentShader_21.txt");




	Shader lightSourceShaderProgram("res/Shaders/Vertex_light_21.txt", "res/Shaders/Fragment_light_21.txt");
	Shader lightSourceShaderProgram1("res/Shaders/Vertex_light_21.txt", "res/Shaders/Fragment_light_21.txt");
	Shader lightSourceShaderProgram2("res/Shaders/Vertex_light_21.txt", "res/Shaders/Fragment_light_21.txt");

	Shader lightSourceShaderProgram3("res/Shaders/Vertex_light_21.txt", "res/Shaders/Fragment_light_21.txt");
	Shader lightSourceShaderProgram4("res/Shaders/Vertex_light_21.txt", "res/Shaders/Fragment_light_21.txt");

	Shader lightSourceShaderProgram5("res/Shaders/Vertex_light_21.txt", "res/Shaders/Fragment_light_21.txt");
	


	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);//ta bazv gia to bathos

	glDepthFunc(GL_LESS);//ta bazv 
	bool animate = true;
	bool show_demo_window = true;
	bool show_another_window = false;
	// Game loop
	bool rotation = true;
	bool rotation1 = true;
	bool rotation2 = true;
	bool rotation3 = true;
	bool rotation4 = true;
	bool rotation5 = true;
	bool rotation6 = true;
	bool rotation7 = true;


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ProcessInput(window);
		//Left_Ctrl(window);

		float time = glfwGetTime();//gia to delta time

		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		//std::cout << deltaTime << std::endl;

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::vec3 lightSourceColor(1.0f, 1.0f, 1.0f);//orismow xrvmatos foros


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();



		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Begin("Tools");
		ImGui::Checkbox("animate", &animate);
		ImGui::Checkbox("Point Lights", &rotation1);


		ImGui::Text("light 1:"); ImGui::SameLine();
		static int e1 = 1;

		ImGui::RadioButton("20", &e1, 1); ImGui::SameLine();
		ImGui::RadioButton("32", &e1, 2); ImGui::SameLine();
		ImGui::RadioButton("50", &e1, 3); ImGui::SameLine();
		ImGui::RadioButton("65", &e1, 4); ImGui::SameLine();
		ImGui::RadioButton("100", &e1, 5);
		ImGui::Checkbox("Point Light ID:0", &rotation);


		glm::vec3 lightSourcePosition1;
		glm::vec3 off;
		glm::vec3 off2;
		glm::vec3 off3;
		glm::vec3 off4;
		glm::vec3 off5;
		glm::vec3 off6;

		float a1;
		float b1;
		float c1;

		float a2;
		float b2;
		float c2;

		float a3;
		float b3;
		float c3;

		float a5;
		float b5;
		float c5;

		if (e1 == 1) {
			a1 = 1.0f;
			b1 = 0.22f;
			c1 = 0.20f;
	}
	else if (e1 == 2)
	{
		a1 = 1.0f;
		b1 = 0.14f;
		c1 = 0.07f;
	}
		
	else if (e1 == 3)
		{
			a1 = 1.0f;
			b1 = 0.09f;
			c1 = 0.032f;
		}
	else if (e1 == 4)
		{
			a1 = 1.0f;
			b1 = 0.07f;
			c1 = 0.017f;
		}
	else 
		{
			a1 = 1.0f;
			b1 = 0.045f;
			c1 = 0.0075f;
		}



		if (rotation && rotation1) {

			 lightSourcePosition1 = glm::vec3(2.3f, -3.3f, -4.0f);

			 off= glm::vec3(1.0f, 1.0f, 1.0f);




		}
		else {
			lightSourcePosition1 = glm::vec3(100.0f, 100.0f, 100.0f);
			off = glm::vec3(0.0f, 0.0f, 0.0f);
		}


		ImGui::End();

		ImGui::Begin("light2");
		ImGui::Text("light 2:"); ImGui::SameLine();
		static int e2 = 1;
		ImGui::RadioButton("20", &e2, 1); ImGui::SameLine();
		ImGui::RadioButton("32", &e2, 2); ImGui::SameLine();
		ImGui::RadioButton("50", &e2, 3); ImGui::SameLine();
		ImGui::RadioButton("65", &e2, 4); ImGui::SameLine();
		ImGui::RadioButton("100", &e2, 5);
		ImGui::Checkbox("Point Light ID:2", &rotation2);
		glm::vec3 lightSourcePosition2;

		if (e2 == 1) {
			a2 = 1.0f;
			b2 = 0.22f;
			c2 = 0.20f;
		}
		else if (e2 == 2)
		{
			a2 = 1.0f;
			b2 = 0.14f;
			c2 = 0.07f;
		}

		else if (e2 == 3)
		{
			a2 = 1.0f;
			b2 = 0.09f;
			c2 = 0.032f;
		}
		else if (e2 == 4)
		{
			a2 = 1.0f;
			b2 = 0.07f;
			c2 = 0.017f;
		}
		else
		{
			a2= 1.0f;
			b2 = 0.045f;
			c2 = 0.0075f;
		}






		if (rotation2 && rotation1) {

			lightSourcePosition2 = glm::vec3(-3.0f, 1.0f, -10.0f);
			off2 = glm::vec3(1.0f, 1.0f, 1.0f);
		}
		else {
			lightSourcePosition2 = glm::vec3(100.0f, 100.0f, 100.0f);
			off2 = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		ImGui::End();

		

		ImGui::Begin("light3");
		ImGui::Text("light 3:"); ImGui::SameLine();
		static int e3 = 1;
		ImGui::RadioButton("20", &e3, 1); ImGui::SameLine();
		ImGui::RadioButton("32", &e3, 2); ImGui::SameLine();
		ImGui::RadioButton("50", &e3, 3); ImGui::SameLine();
		ImGui::RadioButton("65", &e3, 4); ImGui::SameLine();
		ImGui::RadioButton("100", &e3, 5);
		ImGui::Checkbox("Point Light ID:1", &rotation3);

		glm::vec3 lightSourcePosition3;

		if (e3 == 1) {
			a3 = 1.0f;
			b3 = 0.22f;
			c3 = 0.20f;
		}
		else if (e3 == 2)
		{
			a3 = 1.0f;
			b3 = 0.14f;
			c3 = 0.07f;
		}

		else if (e3 == 3)
		{
			a3 = 1.0f;
			b3 = 0.09f;
			c3 = 0.032f;
		}
		else if (e3 == 4)
		{
			a3 = 1.0f;
			b3 = 0.07f;
			c3 = 0.017f;
		}
		else
		{
			a3 = 1.0f;
			b3 = 0.045f;
			c3 = 0.0075f;
		}



		if (rotation3 && rotation1) {

			lightSourcePosition3 = glm::vec3(0.0f, 0.0f, -3.0f);
			off3 = glm::vec3(1.0f, 1.0f, 1.0f);
		}
		else {
			lightSourcePosition3 = glm::vec3(100.0f, 100.0f, 100.0f);
			off3 = glm::vec3(0.0f, 0.0f, 0.0f);
		}



		ImGui::End();
		

		ImGui::Begin("light4");
		ImGui::Text("light 4:"); 
		static float f = 5.0f;
		ImGui::SliderFloat("radius", &f, 2.0f, 10.0f);
		static int e4 = 1;
		ImGui::RadioButton("20", &e4, 1); ImGui::SameLine();
		ImGui::RadioButton("32", &e4, 2); ImGui::SameLine();
		ImGui::RadioButton("50", &e4, 3); ImGui::SameLine();
		ImGui::RadioButton("65", &e4, 4); ImGui::SameLine();
		ImGui::RadioButton("100", &e4, 5);
		ImGui::Checkbox("Point Light Moving", &rotation4);

		glm::vec3 lightSourcePosition4;
		if (e4 == 1) {
			a5 = 1.0f;
			b5 = 0.22f;
			c5 = 0.20f;
		}
		else if (e4 == 2)
		{
			a5 = 1.0f;
			b5 = 0.14f;
			c5 = 0.07f;
		}

		else if (e4 == 3)
		{
			a5 = 1.0f;
			b5 = 0.09f;
			c5 = 0.032f;
		}
		else if (e4 == 4)
		{
			a5 = 1.0f;
			b5 = 0.07f;
			c5 = 0.017f;
		}
		else
		{
			a5 = 1.0f;
			b5 = 0.045f;
			c5 = 0.0075f;
		}


		if (rotation4 && rotation1) {

			lightSourcePosition4 = glm::vec3(0.0f, 0.0f, f);
			off4 = glm::vec3(1.0f, 1.0f, 1.0f);




		}
		else {
			lightSourcePosition4 = glm::vec3(100.0f, 100.0f, 100.0f);
			off4 = glm::vec3(0.0f, 0.0f, 0.0f);
		}




		ImGui::End();
		

		ImGui::Begin("light5-6");
		ImGui::Text("light 5-6:"); 
		

		ImGui::Checkbox("Directional Light ID:4", &rotation5); ImGui::SameLine();
		ImGui::Checkbox("Directional Light ID:6", &rotation6);
		ImGui::Checkbox("Directional Lights", &rotation7);

		glm::vec3 lightSourcePosition5;
		glm::vec3 lightSourceDirection3;
		

		if (rotation5 && rotation7) {

			lightSourceDirection3 = glm::vec3(0.0f, -1.0f, 0.0f);
			lightSourcePosition5 = glm::vec3(0.0f, 10.0f, -10.0f);
			off5 = glm::vec3(1.0f, 1.0f, 1.0f);

		}
		else {
			lightSourceDirection3 = glm::vec3(0.0f, -1.0f, 0.0f);
			lightSourcePosition5 = glm::vec3(100.0f, 100.0f, 100.0f);
			off5 = glm::vec3(0.0f, 0.0f, 0.0f);
		
		}


		glm::vec3 lightSourcePosition6;
		glm::vec3 lightSourceDirection4;
		if (rotation6 && rotation7) {

			lightSourceDirection4 = glm::vec3(1.0f, -1.0f, 0.0f);

			lightSourcePosition6 = glm::vec3(-10.0f, 10.0f, -10.0f);
			off6 = glm::vec3(1.0f, 1.0f, 1.0f);

		}
		else {
			lightSourceDirection4 = glm::vec3(1.0f, -1.0f, 0.0f);
			lightSourcePosition6 = glm::vec3(100.0f, 100.0f, 100.0f);
			off6 = glm::vec3(0.0f, 0.0f, 0.0f);
		
		}



		ImGui::End();


		
		// Render Using the shader program
		shaderProgram.use();

		shaderProgram.setVec3("cameraPosition", myCamera.Position);

		// Material to yliko poy einai ftiagmeno to antikeimeno
		 // epipedo gyalistikothtas  to 0.25f

		// Light Source
		


		glm::mat4 view;
		view = myCamera.GetViewMatrix(); // now we get the view matrix form the camrera class -------------
		shaderProgram.setMat4("view", view);

		glm::mat4 projection;

		// 2D
		//projection = glm::ortho(-5.0f, 5.0f, -6.0f, 6.0f, -15.0f, 18.0f); // the values were chosen to fit the cube positions in each axis

		// 3D
		projection = glm::perspective(glm::radians(myCamera.Zoom), 800.0f / 600.0f, 0.3f, 100.0f); // now we get the zoom form the camera class ---------------------

		shaderProgram.setMat4("projection", projection);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;

			shaderProgram.setVec3("material.ambientColor", glm::vec3(material_ambientColor[i]));
			shaderProgram.setVec3("material.diffuseColor", glm::vec3(material_diffuseColor[i]));
			shaderProgram.setVec3("material.specularColor", glm::vec3(material_specularColor[i]));
			shaderProgram.setFloat("material.shininess", 128.0f * float(material_shininess[i]) );

			shaderProgram.setVec3("lightSource.position", lightSourcePosition1);
			shaderProgram.setVec3("lightSource.position1", lightSourcePosition2);
			shaderProgram.setVec3("lightSource.position2", lightSourcePosition3);
			shaderProgram.setVec3("lightSource.position5", lightSourcePosition4);
			
			
			
			shaderProgram.setVec3("lightSource.direction3", lightSourceDirection[0]);
			shaderProgram.setVec3("lightSource.direction4", lightSourceDirection[1]);
			
			
			// only for directional light
			shaderProgram.setVec3("lightSource.ambientColor", off);
			shaderProgram.setVec3("lightSource.diffuseColor", off);
			shaderProgram.setVec3("lightSource.specularColor", off);

			shaderProgram.setVec3("lightSource.ambientColor1", off2);
			shaderProgram.setVec3("lightSource.diffuseColor1", off2);
			shaderProgram.setVec3("lightSource.specularColor1", off2);

			shaderProgram.setVec3("lightSource.ambientColor2", off3);
			shaderProgram.setVec3("lightSource.diffuseColor2", off3);
			shaderProgram.setVec3("lightSource.specularColor2", off3);

			shaderProgram.setVec3("lightSource.ambientColor3", off5);
			shaderProgram.setVec3("lightSource.diffuseColor3", off5);
			shaderProgram.setVec3("lightSource.specularColor3", off5);


			shaderProgram.setVec3("lightSource.ambientColor4", off6);
			shaderProgram.setVec3("lightSource.diffuseColor4", off6);
			shaderProgram.setVec3("lightSource.specularColor4", off6);

			shaderProgram.setVec3("lightSource.ambientColor5", off4);
			shaderProgram.setVec3("lightSource.diffuseColor5", off4);
			shaderProgram.setVec3("lightSource.specularColor5", off4);






			shaderProgram.setFloat("lightSource.constant", a1);
			shaderProgram.setFloat("lightSource.linear", b1);
			shaderProgram.setFloat("lightSource.quadratic", c1);

			shaderProgram.setFloat("lightSource.constant1", a2);
			shaderProgram.setFloat("lightSource.linear1", b2);
			shaderProgram.setFloat("lightSource.quadratic1", c2);

			shaderProgram.setFloat("lightSource.constant2", a3);
			shaderProgram.setFloat("lightSource.linear2", b3);
			shaderProgram.setFloat("lightSource.quadratic2", c3);

			
			shaderProgram.setFloat("lightSource.constant5", a5);
			shaderProgram.setFloat("lightSource.linear5", b5);
			shaderProgram.setFloat("lightSource.quadratic5", c5);

			

//---------------------------------------------------------------------------------------------
			

			model = glm::translate(identity, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f) * i, glm::vec3(1.0f, 0.3f, 0.5f));

			shaderProgram.setMat4("model", model);

			glm::mat3 normalTransformation = glm::transpose(glm::inverse(glm::mat3(model)));
			shaderProgram.setMat3("normalTransformation", normalTransformation);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}




		glm::mat4 mami(1.0f);
		glm::mat4 pasxa(1.0f);

		// Render Using the light source shader program gia to fvtismo kai to montelo fung
		lightSourceShaderProgram.use();
		//lightSourceShaderProgram.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
		lightSourceShaderProgram.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram.setMat4("view", view);
		lightSourceShaderProgram.setMat4("projection", projection);

		glm::mat4 model_light = glm::translate(identity, lightSourcePosition1);
		lightSourceShaderProgram.setMat4("model", model_light);
		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami10 = glGetUniformLocation(lightSourceShaderProgram4.ID, "mami");
		glUniformMatrix4fv(mami10, 1, GL_FALSE, &mami[0][0]);

		pasxa = glm::rotate(pasxa, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		int pasxa10 = glGetUniformLocation(lightSourceShaderProgram4.ID, "pasxa");
		glUniformMatrix4fv(pasxa10, 1, GL_FALSE, &pasxa[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//-----------------------------------------------
		lightSourceShaderProgram1.use();

		lightSourceShaderProgram1.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram1.setMat4("view", view);
		lightSourceShaderProgram1.setMat4("projection", projection);

		glm::mat4 model_light1 = glm::translate(identity, lightSourcePosition2);
		lightSourceShaderProgram1.setMat4("model", model_light1);
		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami4 = glGetUniformLocation(lightSourceShaderProgram4.ID, "mami");
		glUniformMatrix4fv(mami4, 1, GL_FALSE, &mami[0][0]);

		pasxa = glm::rotate(pasxa, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		int pasxa4 = glGetUniformLocation(lightSourceShaderProgram4.ID, "pasxa");
		glUniformMatrix4fv(pasxa4, 1, GL_FALSE, &pasxa[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//---------------------------------------------------
		lightSourceShaderProgram2.use();

		lightSourceShaderProgram2.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram2.setMat4("view", view);
		lightSourceShaderProgram2.setMat4("projection", projection);

		glm::mat4 model_light2 = glm::translate(identity, lightSourcePosition3);
		lightSourceShaderProgram2.setMat4("model", model_light2);
		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami3 = glGetUniformLocation(lightSourceShaderProgram4.ID, "mami");
		glUniformMatrix4fv(mami3, 1, GL_FALSE, &mami[0][0]);

		pasxa = glm::rotate(pasxa, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		int pasxa3 = glGetUniformLocation(lightSourceShaderProgram4.ID, "pasxa");
		glUniformMatrix4fv(pasxa3, 1, GL_FALSE, &pasxa[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//--------------------------------------------------------
		lightSourceShaderProgram3.use();

		lightSourceShaderProgram3.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram3.setMat4("view", view);
		lightSourceShaderProgram3.setMat4("projection", projection);

		glm::mat4 model_light3 = glm::translate(identity, lightSourcePosition5);
		lightSourceShaderProgram3.setMat4("model", model_light3);
		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami2 = glGetUniformLocation(lightSourceShaderProgram4.ID, "mami");
		glUniformMatrix4fv(mami2, 1, GL_FALSE, &mami[0][0]);

		pasxa = glm::rotate(pasxa, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		int pasxa2 = glGetUniformLocation(lightSourceShaderProgram4.ID, "pasxa");
		glUniformMatrix4fv(pasxa2, 1, GL_FALSE, &pasxa[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		//------------------------------------------------
		lightSourceShaderProgram4.use();

		lightSourceShaderProgram4.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram4.setMat4("view", view);
		lightSourceShaderProgram4.setMat4("projection", projection);

		glm::mat4 model_light4 = glm::translate(identity, lightSourcePosition6);
		lightSourceShaderProgram4.setMat4("model", model_light4);
		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami1 = glGetUniformLocation(lightSourceShaderProgram4.ID, "mami");
		glUniformMatrix4fv(mami1, 1, GL_FALSE, &mami[0][0]);

		pasxa = glm::rotate(pasxa, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		int pasxa0 = glGetUniformLocation(lightSourceShaderProgram4.ID, "pasxa");
		glUniformMatrix4fv(pasxa0, 1, GL_FALSE, &pasxa[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//------------------------------------------------------
		lightSourceShaderProgram5.use();

		glm::vec3 rotaionAxis;


		rotaionAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		
		lightSourceShaderProgram5.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram5.setMat4("view", view);
		lightSourceShaderProgram5.setMat4("projection", projection);

		
		glm::mat4 model_light5 = glm::translate(identity, lightSourcePosition4);
		model_light5 = glm::translate(model_light5, glm::vec3(0.0f, 0.0f, f));
		//model_light5 = glm::rotate(model_light5, glm::radians(time * 60.0f), rotaionAxis);

		lightSourceShaderProgram5.setMat4("model", model_light5);

		mami = glm::translate(mami, glm::vec3(0.0f, 0.0f, 0.0f));
		int mami22 = glGetUniformLocation(lightSourceShaderProgram5.ID, "mami");
		glUniformMatrix4fv(mami22, 1, GL_FALSE, &mami[0][0]);

		glm::vec3 rotaionAxis3 = glm::vec3(mami22, 0.0f, 0.0f);
		pasxa = glm::rotate(pasxa, glm::radians(time * 30.0f), rotaionAxis3);

		int pasxa1 = glGetUniformLocation(lightSourceShaderProgram5.ID, "pasxa");
		glUniformMatrix4fv(pasxa1, 1, GL_FALSE, &pasxa[0][0]);



		glDrawArrays(GL_TRIANGLES, 0, 36);
//------------------------------------------------------------------------




		

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