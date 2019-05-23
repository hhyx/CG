#include "HW8.h"

HW8::HW8() {
	HW8LinkShader();
}


HW8::~HW8() {
	
}

void HW8::HW8LinkShader() {
	shader = Shader("HW8/HW8.vs", "HW8/HW8.fs");
}

unsigned int HW8::getShaderProgram() {
	return shader.ID;
}

void HW8::drawPoint(vector<pair<float, float> > point, int state) {
	float* po = new float[point.size() * 3];
	for (int i = 0; i < point.size(); i++) {
		po[3 * i] = (point[i].first - 400) / 400.0;
		po[3 * i + 1] = (300 - point[i].second) / 300.0;
		po[3 * i + 2] = 0.0;
	}

	shader.use();
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(po[0]) * point.size() * 3, po, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO);
	if (state == 0)
		glPointSize(1.0f);
	else if (state == 1)
		glPointSize(5.0f);
	else if (state == 2)
		glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, point.size());

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete[] po;
}

void HW8::drawLine(vector<pair<float, float> > point) {
	float* po = new float[point.size() * 3];
	for (int i = 0; i < point.size(); i++) {
		po[3 * i] = (point[i].first- 400)/400.0;
		po[3 * i + 1] = (300-point[i].second)/300.0;
		po[3 * i + 2] = 0.0;
	}

	shader.use();
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(po[0]) * point.size() * 3, po, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, point.size());
		 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete[] po;
}

void HW8::Bezier(float x, float y, int state, bool dynamic) {
	if (state == 1) {
		pair<float, float> p(x, y);
		coordinate.push_back(p);
	}
	else if (state == 3){
		if (!coordinate.empty())
			coordinate.pop_back();
	}

	drawPoint(coordinate, 2);

	vector<pair<float, float>> bezier;
	for (int j = 0; j < 1000; j++) {
		float Q_x = 0;
		float Q_y = 0;
		vector<pair<float, float> >::iterator it = coordinate.begin(), end = coordinate.end();
		for (int i = 0; it != end; ++it, i++) {
			Q_x += it->first * B(i, coordinate.size()-1, j / 1000.0);
			Q_y += it->second * B(i, coordinate.size()-1, j / 1000.0);
		}

		pair<float, float> p(Q_x, Q_y);
		bezier.push_back(p);
	}

	drawPoint(bezier, 0);

	drawLine(coordinate);

	if (dynamic) {
		if (state == 1 || state == 3)
			ratio = 0.0;

		vector<pair<float, float> > point_ = coordinate;
		int n = point_.size() - 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n-i; j++) {
				float Q_x = ratio*(point_[j + 1].first - point_[j].first) + point_[j].first;
				float Q_y = ratio * (point_[j + 1].second - point_[j].second) + point_[j].second;
				pair<float, float> p(Q_x, Q_y);
				point_[j] = p;
			}
			drawLine(point_);
			drawPoint(point_, 1);
		}

		ratio += 1.0f / 1000;
		if (ratio >= 1.0)
			ratio = 0.0;
	}
}

float HW8::B(int i, int n, float t) {
	float res = 1;
	int max_ = i > n - i ? i : n - i;
	int min_ = i < n - i ? i : n - i;

	for (int j = n; j > max_; j--)
		res *= j;
	for (int j = min_; j > 1; j--) {
		res /= j;
	}
	res *= pow(t, i);
	res *= pow(1 - t, n - i);
	return res;
}
