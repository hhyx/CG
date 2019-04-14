#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <include/imgui.h>
#include <include/imgui_impl_glfw.h>
#include <include/imgui_impl_opengl3.h>
#include <include/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
using namespace std;

class HW5
{
public:
	HW5();
	~HW5();
	void HW5LinkShader();
	unsigned int getShaderProgram();
	void draw();
	void cube();
	void projection(float left, float right, float bottom, float top, float znear, float zfar, bool flag);
	void viewChange();
	void useCamera(Camera camera);
private:
	unsigned int shaderProgram;
	unsigned int VAO, VBO, EBO;
};