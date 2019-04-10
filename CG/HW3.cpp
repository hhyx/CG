#include "HW3.h"

// 顶点着色器
const char *HW3vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor; \n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = aColor;\n"
"}\0";

// 片段着色器
const char *HW3fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

HW3::HW3() 
{
	HW3LinkShader();
}
HW3::~HW3()
{
	glDeleteProgram(shaderProgram);
}

void HW3::HW3LinkShader()
{
	// 顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &HW3vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 检查顶点着色器出错
	int success;
	char infoLog[521];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &HW3fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 检查片段着色器出错
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 链接着色器
	unsigned int shaderProgram_;
	shaderProgram_ = glCreateProgram();
	glAttachShader(shaderProgram_, vertexShader);
	glAttachShader(shaderProgram_, fragmentShader);
	glLinkProgram(shaderProgram_);

	// 链接后删除无用的着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 检查链接着色器出错
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = shaderProgram_;
}

unsigned int HW3::getShaderProgram() {
	return shaderProgram;
}

void HW3::drawPoints(int x1, int y1, int x2, int y2)
{
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	bool angle = true; // 角度小于45度
	if (dx < dy)
	{
		angle = false;
		swap(x1, y1);
		swap(x2, y2);
		swap(dx, dy);
	}

	int ix = x2 > x1 ? 1 : -1;
	int iy = y2 > y1 ? 1 : -1;
	int x = x1, y = y1;
	int d = dy * 2 - dx;
	int dy2 = 2 * dy;
	int dydx2 = 2 * (dy - dx);

	if (angle)
	{
		while (x != x2)
		{
			if (d < 0)
			{
				d += dy2;
			}
			else
			{
				y += iy;
				d += dydx2;
			}
			float poi[] = {
				float(x - 40)*1.0f / 40.0f, float(y - 30)*1.0f / 30.0f, 0.0f
			};
			unsigned int VBO;
			glGenBuffers(1, &VBO);
			unsigned int VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(poi), poi, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glBindVertexArray(VAO);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, 1);

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			x += ix;
		}
	}
	else
	{
		while (x != x2)
		{
			if (d < 0)
			{
				d += dy2;
			}
			else
			{
				y += iy;
				d += dydx2;
			}

			float poi[] = {
				float(y - 40)*1.0f / 40.0f, float(x - 30)*1.0f / 30.0f, 0.0f
			};
			unsigned int VBO;
			glGenBuffers(1, &VBO);
			unsigned int VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(poi), poi, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glBindVertexArray(VAO);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, 1);

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			x += ix;
		}
	}
}

vector<int> HW3::getEquation(int x1, int y1, int x2, int y2)
{
	vector<int> equation;
	equation.push_back(y2 - y1);
	equation.push_back(x1 - x2);
	equation.push_back(x2 * y1 - x1 * y2);
	return equation;
}

void HW3::drawTriangles(int x1, int y1, int x2, int y2, int x3, int y3)
{
	vector<vector<int>> lines;
	lines.push_back(getEquation(x1, y1, x2, y2));
	lines.push_back(getEquation(x1, y1, x3, y3));
	lines.push_back(getEquation(x2, y2, x3, y3));

	// 调整方程方向
	for (int i = 0; i < 3; i++)
	{
		int x, y;
		if (i == 0)
		{
			x = x3, y = y3;
		}
		else if (i == 1)
		{
			x = x2, y = y2;
		}
		else if (i == 2)
		{
			x = x1, y = y1;
		}

		if (lines[i][0] * x + lines[i][1] * y + lines[i][2] < 0)
		{
			lines[i][0] *= -1;
			lines[i][1] *= -1;
			lines[i][2] *= -1;
		}
	}

	int maxx = max(x1, max(x2, x3));
	int minx = min(x1, min(x2, x3));
	int maxy = max(y1, max(y2, y3));
	int miny = min(y1, min(y2, y3));

	for (int x = minx; x <= maxx; x++)
	{
		for (int y = miny; y <= maxy; y++)
		{
			bool inside = true;
			for (int i = 0; i < 3; i++)
			{
				if (lines[i][0] * x + lines[i][1] * y + lines[i][2] < 0)
				{
					inside = false;
					break;
				}
			}
			if (inside)
			{
				float poi[] = {
					float(x - 40)*1.0f / 40.0f, float(y - 30)*1.0f / 30.0f, 0.0f
				};
				unsigned int VBO;
				glGenBuffers(1, &VBO);
				unsigned int VAO;
				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);

				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(poi), poi, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				glBindVertexArray(VAO);
				glPointSize(5.0f);
				glDrawArrays(GL_POINTS, 0, 1);

				glDeleteVertexArrays(1, &VAO);
				glDeleteBuffers(1, &VBO);
			}
		}
	}
}

void HW3::drawCircles(int x, int y, int r)
{
	int x_ = 0, y_ = r;
	int d = 3 - 2 * r;

	while (x_ <= y_)
	{
		drawCircles2(x, y, x_, y_);
		if (d < 0)
		{
			d += 4 * x_ + 6;
		}
		else
		{
			d += 4 * (x_ - y_) + 10;
			y_--;
		}
		x_++;
	}


}

void HW3::drawCircles2(int x, int y, int x_, int y_)
{
	//cout << x << " " << y << " " << x_ << " " << y_ << endl;
	float poi[] = {
		float(x + x_ - 40)*1.0f / 40.0f, float(y + y_ - 30)*1.0f / 30.0f, 0.0f,
		float(x - x_ - 40)*1.0f / 40.0f, float(y + y_ - 30)*1.0f / 30.0f, 0.0f,
		float(x + x_ - 40)*1.0f / 40.0f, float(y - y_ - 30)*1.0f / 30.0f, 0.0f,
		float(x - x_ - 40)*1.0f / 40.0f, float(y - y_ - 30)*1.0f / 30.0f, 0.0f,
		float(x + y_ - 40)*1.0f / 40.0f, float(y + x_ - 30)*1.0f / 30.0f, 0.0f,
		float(x - y_ - 40)*1.0f / 40.0f, float(y + x_ - 30)*1.0f / 30.0f, 0.0f,
		float(x + y_ - 40)*1.0f / 40.0f, float(y - x_ - 30)*1.0f / 30.0f, 0.0f,
		float(x - y_ - 40)*1.0f / 40.0f, float(y - x_ - 30)*1.0f / 30.0f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(poi), poi, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 8);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}