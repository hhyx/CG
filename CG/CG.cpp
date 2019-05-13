#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "HW3/HW3.h"
#include "HW4/HW4.h"
#include "HW5/HW5.h"
#include "HW6/HW6.h"
#include "HW7/HW7.h"
#include "Camera.h"
#include "shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main() {
	// 实例化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口对象
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "CG", NULL, NULL);
	if (window == NULL)	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// 视口
	glViewport(0, 0, screenWidth, screenHeight);

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

	bool hw5Flag = false;
	bool cube = false;
	bool orthographic = false;
	bool perspective = false;
	float left = -2, right = 1, bottom = -1, top = 1.5, znear = -30, zfar = 30;
	bool viewChange = false;
	bool cameraFlag = false;
	HW5 hw5;

	bool hw6Flag = false;
	bool phong = false;
	bool gouraud = false;
	bool dynamic = false;
	float ambientStrength = 0.1;
	float diffuseStrength = 0.0;
	float specularStrength = 0.5;
	int Reflectivity = 32;
	float x = 0.0f;
	HW6 hw6;

	bool hw7Flag = false;
	bool shadow = false;
	float hw7x = -2.0f, hw7y = 4.0f, hw7z = -1.0f;
	HW7 hw7 = HW7(screenWidth, screenHeight);

	// 渲染循环
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			if (!hw4Flag && !hw3Flag && !hw5Flag && !hw6Flag && !hw7Flag) {
				choose = -1;
			}

			ImGui::Begin("HW");
			ImGui::RadioButton("HW3", &choose, 0);
			ImGui::RadioButton("HW4", &choose, 1);
			ImGui::RadioButton("HW5", &choose, 2);
			ImGui::RadioButton("HW6", &choose, 3);
			ImGui::RadioButton("HW7", &choose, 4);

			switch (choose) {
			case 0:
				hw3Flag = true;
				hw4Flag = hw5Flag = hw6Flag = hw7Flag = false;
				break;
			case 1:
				hw4Flag = true;
				hw3Flag = hw5Flag = hw6Flag = hw7Flag = false;
				break;
			case 2:
				hw5Flag = true;
				hw3Flag = hw4Flag = hw6Flag = hw7Flag = false;
				break;
			case 3:
				hw6Flag = true;
				hw3Flag = hw4Flag = hw5Flag = hw7Flag = false;
				break;
			case 4:
				hw7Flag = true;
				hw3Flag = hw4Flag = hw5Flag = hw6Flag = false;
				break;
			default:
				break;
			}

			ImGui::End();
		}

		if (hw3Flag) {
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

		if (hw4Flag) {
			shaderProgram = hw4.getShaderProgram();
			ImGui::Begin("HW4", &hw4Flag);
			ImGui::Checkbox("DepthTest", &depthTest);
			ImGui::Checkbox("Animation", &animation);
			ImGui::Checkbox("Translation", &translation);
			ImGui::Checkbox("Rotation", &rotation);
			ImGui::Checkbox("Scaling", &scaling);
			ImGui::End();
		}

		if (hw5Flag) {
			shaderProgram = hw5.getShaderProgram();
			ImGui::Begin("HW5", &hw5Flag);
			ImGui::Checkbox("cube", &cube);
			ImGui::Checkbox("orthographic", &orthographic);
			ImGui::Checkbox("perspective", &perspective);
			ImGui::SliderFloat("left", &left, -3.0, 3);
			ImGui::SliderFloat("right", &right, -3.0, 3);
			ImGui::SliderFloat("bottom", &bottom, -3.0, 3);
			ImGui::SliderFloat("top", &top, -3.0, 3);
			ImGui::SliderFloat("near", &znear, -50, 50);
			ImGui::SliderFloat("far", &zfar, -50, 50);
			ImGui::Checkbox("viewChange", &viewChange);
			ImGui::Checkbox("camera", &cameraFlag);
			ImGui::End();
		}

		if (hw6Flag) {
			ImGui::Begin("HW6", &hw6Flag);
			ImGui::Checkbox("Phong Shading", &phong);
			ImGui::Checkbox("Gourud Shading", &gouraud);
			ImGui::Checkbox("Dynamic", &dynamic);
			ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
			ImGui::SliderFloat("diffuseStrength", &diffuseStrength, 0.0f, 1.0f);
			ImGui::SliderFloat("specularStrength", &specularStrength, 0.0, 1.0f);
			ImGui::SliderInt("Reflectivity", &Reflectivity, 1, 256);
			ImGui::SliderFloat("x", &x, -5.0f, 1.0f);
			ImGui::End();
			if (phong)
			{
				shaderProgram = hw6.getShaderProgramPhone();
			}
			else if (gouraud)
			{
				shaderProgram = hw6.getShaderProgramGouraud();
			}
		}

		if (hw7Flag) {
			shaderProgram = hw7.getShaderProgram();
			ImGui::Begin("HW7", &hw7Flag);
			ImGui::Checkbox("Shadow", &shadow);
			ImGui::SliderFloat("x", &hw7x, -10.0f, 10.0f);
			ImGui::SliderFloat("y", &hw7y, -10.0f, 10.0f);
			ImGui::SliderFloat("z", &hw7z, -10.0f, 10.0f);
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

		if (hw3Flag) {
			if (drawPoint) {
				hw3.drawPoints(x1, y1, x2, y2);
				hw3.drawPoints(x2, y2, x3, y3);
				hw3.drawPoints(x3, y3, x1, y1);
			}
			if (drawCircle)	{
				hw3.drawCircles(40, 30, radius);
			}
			if (drawTriangle) {
				hw3.drawTriangles(x1, y1, x2, y2, x3, y3);
			}
		}

		if (hw4Flag) {
			if (depthTest) {
				hw4.StartDepthTest();
			}
			if (animation) {
				hw4.Animation();
			}
			if (translation) {
				hw4.Translation();
			}
			if (rotation) {
				hw4.Rotation();
			}
			if (scaling) {
				hw4.Scaling();
			}
		}

		if (hw5Flag) {
			if (cube) {
				hw5.cube();
			}
			if (orthographic) {
				hw5.projection(left, right, bottom, top, znear, zfar, true);
			}
			if (perspective) {
				hw5.projection(left, right, bottom, top, znear, zfar, false);
			}
			if (viewChange) {
				hw5.viewChange();
			}
			if (cameraFlag) {
				glfwSetCursorPosCallback(window, mouse_callback);
				glfwSetScrollCallback(window, scroll_callback);
				// tell GLFW to capture our mouse
				//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				hw5.useCamera(camera);
			}
		}

		if (hw6Flag) {
			//glfwSetCursorPosCallback(window, mouse_callback);
			glfwSetScrollCallback(window, scroll_callback);

			if (phong) {
				hw6.Phong(camera, dynamic, ambientStrength, diffuseStrength, specularStrength, Reflectivity, x);
			}
			if (gouraud) {
				hw6.Gouraud(camera, dynamic, ambientStrength, diffuseStrength, specularStrength, Reflectivity, x);
			}
		}

		if (hw7Flag) {
			glfwSetCursorPosCallback(window, mouse_callback);
			glfwSetScrollCallback(window, scroll_callback);
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (shadow) {
				hw7.shadow(camera, hw7x, hw7y, hw7z);
			}
		}

		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}