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
using namespace std;

class HW4
{
public:
	HW4();
	~HW4();
	void HW4LinkShader();
	unsigned int getShaderProgram();
	void draw();
	void getPicture();
	void StartDepthTest();
	void Animation();
	void Translation();
	void Rotation();
	void Scaling();
private:
	unsigned int texture1;
	unsigned int texture2;
	unsigned int shaderProgram;
	unsigned int VBO, VAO;
};