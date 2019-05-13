#include "HW4.h"

// 顶点着色器
const char *HW4vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection; "
"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);;"
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y); "
"}\0";

// 片段着色器
const char *HW4fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
"}\n\0";

float HW4vertices[] = {
	-2.0f, -2.0f, -2.0f,  0.0f, 0.0f,
	 2.0f, -2.0f, -2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	-2.0f,  2.0f, -2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 0.0f,

	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	 2.0f, -2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 1.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 1.0f,
	-2.0f,  2.0f,  2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,

	-2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	-2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	-2.0f,  2.0f,  2.0f,  1.0f, 0.0f,

	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,

	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f, -2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f, -2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f, -2.0f,  2.0f,  1.0f, 0.0f,
	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,

	-2.0f,  2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	-2.0f,  2.0f,  2.0f,  0.0f, 0.0f,
	-2.0f,  2.0f, -2.0f,  0.0f, 1.0f
};

HW4::HW4() {
	HW4LinkShader();
	getPicture();
	draw();
}

HW4::~HW4() {
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void HW4::HW4LinkShader()
{
	// 顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &HW4vertexShaderSource, NULL);
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
	glShaderSource(fragmentShader, 1, &HW4fragmentShaderSource, NULL);
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
	glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = shaderProgram_;
}

unsigned int HW4::getShaderProgram() {
	return shaderProgram;
}

void HW4::getPicture()
{
	/*unsigned int texture1;
	unsigned int texture2;*/

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("image/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("image/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

}

void HW4::draw()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HW4vertices), HW4vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable(GL_DEPTH_TEST);
}

void HW4::StartDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void HW4::Animation()
{
	glBindVertexArray(VAO);
	StartDepthTest();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3((float)cos(glfwGetTime()), (float)cos(glfwGetTime()), (float)sin(glfwGetTime())));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3((float)sin(glfwGetTime())*5.5, (float)cos(glfwGetTime())*5.5, -12.0f));
	view = glm::translate(view, glm::vec3(0.1, 0.0f, -2.0f));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f) * 3, glm::vec3(0.5f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3((float)cos(glfwGetTime()), (float)cos(glfwGetTime()), (float)cos(glfwGetTime())));
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.1f, 0.0f, -15.0f));
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void HW4::Translation()
{
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(4 * (float)sin(glfwGetTime()), 0.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -12.0f));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisable(GL_DEPTH_TEST);
}

void HW4::Rotation()
{
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -12.0f));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisable(GL_DEPTH_TEST);
}

void HW4::Scaling()
{
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(abs((float)sin(glfwGetTime())), abs((float)sin(glfwGetTime())), abs((float)sin(glfwGetTime()))));
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -12.0f));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisable(GL_DEPTH_TEST);
}