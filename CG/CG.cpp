#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "HW3.h"
#include "HW4.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;

int main()
{
	// 实例化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口对象
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "CG", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// 视口
	glViewport(0, 0, screenWidth, screenHeight);

	// 当调整窗口同时调整视口
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 创建并绑定ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsClassic();
	ImGui_ImplOpenGL3_Init("#version 330");
	
	// 链接着色器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glLinkProgram(shaderProgram);

	int choose = -1;
	bool hw3Flag = false;
	bool drawPoint = false;
	bool drawTriangle = false;
	bool drawCircle = false;
	int x1 = 10, y1 = 10;
	int x2 = 40, y2 = 40;
	int x3 = 60, y3 = 20;
	int radius = 10;
	HW3 hw3;

	bool hw4Flag = false;
	bool animation = false;
	bool depthTest = false;
	bool translation = false;
	bool rotation = false;
	bool scaling = false;
	HW4 hw4;

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			if (!hw4Flag && !hw3Flag)
			{
				choose = -1;
			}

			ImGui::Begin("HW");
			ImGui::RadioButton("HW3", &choose, 0);
			ImGui::RadioButton("HW4", &choose, 1);

			switch (choose)
			{
			case 0:
				hw3Flag = true;
				hw4Flag = false;
				break;
			case 1:
				hw4Flag = true;
				hw3Flag = false;
				break;
			default:
				break;
			}
			
			ImGui::End();
		}

		if (hw3Flag)
		{	
			shaderProgram = hw3.getShaderProgram();
			ImGui::Begin("HW3", &hw3Flag);
			ImGui::Checkbox("no fill triangle", &drawPoint);
			ImGui::Checkbox("fill triangle", &drawTriangle);
			ImGui::SliderInt("x1", &x1, 0, 80);
			ImGui::SliderInt("y1", &y1, 0, 60);
			ImGui::SliderInt("x2", &x2, 0, 80);
			ImGui::SliderInt("y2", &y2, 0, 60);
			ImGui::SliderInt("x3", &x3, 0, 80);
			ImGui::SliderInt("y3", &y3, 0, 60);
			ImGui::Checkbox("circle", &drawCircle);
			ImGui::SliderInt("radius", &radius, 0, 30);
			ImGui::End();
		}

		if (hw4Flag)
		{
			shaderProgram = hw4.getShaderProgram();
			ImGui::Begin("HW4", &hw4Flag);
			ImGui::Checkbox("DepthTest", &depthTest);
			ImGui::Checkbox("Animation", &animation);
			ImGui::Checkbox("Translation", &translation);
			ImGui::Checkbox("Rotation", &rotation);
			ImGui::Checkbox("Scaling", &scaling);
			ImGui::End();
		}

		glUseProgram(shaderProgram);
		
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (hw3Flag)
		{
			if (drawPoint)
			{
				hw3.drawPoints(x1, y1, x2, y2);
				hw3.drawPoints(x2, y2, x3, y3);
				hw3.drawPoints(x3, y3, x1, y1);
			}
			if (drawCircle)
			{
				hw3.drawCircles(40, 30, radius);
			}
			if (drawTriangle)
			{
				hw3.drawTriangles(x1, y1, x2, y2, x3, y3);
			}
		}

		if (hw4Flag)
		{
			if (depthTest)
			{
				hw4.StartDepthTest();
			}
			if (animation)
			{
				hw4.Animation();
			}
			if (translation)
			{
				hw4.Translation();
			}
			if (rotation)
			{
				hw4.Rotation();
			}
			if (scaling)
			{
				hw4.Scaling();
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}