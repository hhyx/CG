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
#include "shader.h"
using namespace std;

class HW7
{
public:
	HW7(GLuint, GLuint);
	~HW7();
	void HW7LinkShader();
	unsigned int getShaderProgram();
	void draw();
	void shadow(Camera, float, float, float);
	void RenderScene(Shader &);
	void RenderCube();
	void RenderQuad();
	unsigned int loadTexture(char const * path);

private:
	unsigned int planeVAO, planeVBO, cubeVAO = 0, cubeVBO, quadVAO = 0, quadVBO;
	GLuint depthMapFBO;
	GLuint depthMap;
	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint SCR_WIDTH, SCR_HEIGHT;
	Shader simpleDepthShader, debugDepthQuad, shader;
	unsigned int woodTexture;
};