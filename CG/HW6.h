#pragma once
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

class HW6
{
public:
	HW6();
	~HW6();
	void HW6LinkShader();
	unsigned int getShaderProgramPhone();
	unsigned int getShaderProgramGouraud();
	void draw();
	void Phong(Camera camera, bool, float ,float ,float, int, float);
	void Gouraud(Camera camera, bool, float, float, float, int, float);

private:
	unsigned int shaderProgramPhone, shaderProgramGouraud, shaderProgramLight;
	unsigned int VAO, lightVAO, VBO;
};