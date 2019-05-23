#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <include/imgui.h>
#include <include/imgui_impl_glfw.h>
#include <include/imgui_impl_opengl3.h>
#include <include/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
using namespace std;

class HW8 {
public:
	HW8();
	~HW8();
	void HW8LinkShader();
	unsigned int getShaderProgram();
	void drawPoint(vector<pair<float, float> >, int);
	void drawLine(vector<pair<float, float> >);
	void Bezier(float x, float y, int, bool);
	float B(int, int, float);

private:
	Shader shader;
	vector<pair<float, float>> coordinate;
	float ratio = 0.0;
};

