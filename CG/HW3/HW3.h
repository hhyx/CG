#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <include/imgui.h>
#include <include/imgui_impl_glfw.h>
#include <include/imgui_impl_opengl3.h>
using namespace std;

class HW3
{
public:
	HW3();
	~HW3();
	void HW3LinkShader();
	unsigned int getShaderProgram();
	void drawPoints(int x1, int y1, int x2, int y2);
	// Edge Walking
	vector<int> getEquation(int x1, int y1, int x2, int y2);
	void drawTriangles(int x1, int y1, int x2, int y2, int x3, int y3);
	void drawCircles(int x, int y, int r);
	void drawCircles2(int x, int y, int x_, int y_);
private:
	unsigned int shaderProgram;
};