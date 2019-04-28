#include "HW6.h"

// 顶点着色器
const char *HW6vertexShaderSourcePhone =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec3 aColor; \n"
"out vec3 ourColor;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 Normal;\n"
"out vec3 FragPos;\n"
"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"	FragPos = vec3(model * vec4(aPos, 1.0));\n"
"	Normal = mat3(transpose(inverse(model))) * aNormal;\n"
"	ourColor = aColor;\n "
"}\n\0";

const char *HW6vertexShaderSourceGouraud =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;"
"layout(location = 1) in vec3 aNormal;"
"layout (location = 2) in vec3 aColor; \n"
"out vec3 ourColor;\n"

"out vec3 LightingColor;"
"uniform float ambientStrength;"
"uniform float diffuseStrength;"
"uniform float specularStrength;"
"uniform int Reflectivity;"
"uniform vec3 lightPos;"
"uniform vec3 viewPos;"
"uniform vec3 lightColor;"

"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"

"void main()"
"{"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);"

"	vec3 Position = vec3(model * vec4(aPos, 1.0));"
"	vec3 Normal = mat3(transpose(inverse(model))) * aNormal;"

"	vec3 ambient = ambientStrength * lightColor;"

"	vec3 norm = normalize(Normal);"
"	vec3 lightDir = normalize(lightPos - Position);"
"	float diff = max(dot(norm, lightDir), diffuseStrength);"
"	vec3 diffuse = diff * lightColor;"

"	vec3 viewDir = normalize(viewPos - Position);"
"	vec3 reflectDir = reflect(-lightDir, norm);"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Reflectivity);"
"	vec3 specular = specularStrength * spec * lightColor;"

"	LightingColor = ambient + diffuse + specular;"
"	ourColor = aColor;"
"}";

// 片段着色器
const char *HW6fragmentShaderSourcePhone =
"#version 330 core\n"
"in vec3 Normal;\n"
"in vec3 FragPos;\n"

"out vec4 FragColor;\n"

"uniform float ambientStrength;\n"
"uniform float diffuseStrength;\n"
"uniform float specularStrength;\n"
"uniform int Reflectivity;\n"

"uniform vec3 lightPos;\n"
"uniform vec3 viewPos;\n"

"in vec3 ourColor;\n"

"uniform vec3 lightColor;\n "
"void main()\n"
"{\n"
"	vec3 ambient = ambientStrength * lightColor;\n"

"	vec3 norm = normalize(Normal);\n"
"	vec3 lightDir = normalize(lightPos - FragPos);\n"
"	float diff = max(dot(norm, lightDir), diffuseStrength);\n"
"	vec3 diffuse = diff * lightColor;\n"

"	vec3 viewDir = normalize(viewPos - FragPos);\n"
"	vec3 reflectDir = reflect(-lightDir, norm);\n"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Reflectivity);\n"
"	vec3 specular = specularStrength * spec * lightColor;"

"	vec3 result = (ambient + diffuse + specular) * ourColor;"
"	FragColor = vec4(result, 1.0);\n"
"}\n\0";

const char *HW6fragmentShaderSourceGouraud =
"#version 330 core\n"
"out vec4 FragColor;"

"in vec3 LightingColor;"

"in vec3 ourColor;\n"

"void main()"
"{"
"	FragColor = vec4(LightingColor * ourColor, 1.0);"
"}";

const char *HW6fragmentShaderSourceLight =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0);\n"
"}\n\0";

float HW6vertices[] = {
//  coordinate			  normal vector        color
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.5f, 0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.5f, 0.5f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.5f, 0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.5f, 1.0f, 0.5f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.5f, 1.0f, 0.5f
};

HW6::HW6() {
	HW6LinkShader();
	draw();
}

HW6::~HW6() {
	glDeleteProgram(shaderProgramPhone);
	glDeleteProgram(shaderProgramLight);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
}

void HW6::HW6LinkShader()
{
	// 顶点着色器
	unsigned int vertexShaderPhone;
	vertexShaderPhone = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderPhone, 1, &HW6vertexShaderSourcePhone, NULL);
	glCompileShader(vertexShaderPhone);

	// 检查顶点着色器出错
	int success;
	char infoLog[521];
	glGetShaderiv(vertexShaderPhone, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderPhone, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int vertexShaderGouraud;
	vertexShaderGouraud = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderGouraud, 1, &HW6vertexShaderSourceGouraud, NULL);
	glCompileShader(vertexShaderGouraud);

	glGetShaderiv(vertexShaderGouraud, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderGouraud, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 片段着色器
	unsigned int fragmentShaderPhone;
	fragmentShaderPhone = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderPhone, 1, &HW6fragmentShaderSourcePhone, NULL);
	glCompileShader(fragmentShaderPhone);

	// 检查片段着色器出错
	glGetShaderiv(fragmentShaderPhone, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderPhone, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShaderGouraud;
	fragmentShaderGouraud = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderGouraud, 1, &HW6fragmentShaderSourceGouraud, NULL);
	glCompileShader(fragmentShaderGouraud);

	glGetShaderiv(fragmentShaderGouraud, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderGouraud, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShaderLight;
	fragmentShaderLight = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderLight, 1, &HW6fragmentShaderSourceLight, NULL);
	glCompileShader(fragmentShaderLight);

	glGetShaderiv(fragmentShaderLight, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderLight, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 链接着色器
	unsigned int shaderProgramPhone_;
	shaderProgramPhone_ = glCreateProgram();
	glAttachShader(shaderProgramPhone_, vertexShaderPhone);
	glAttachShader(shaderProgramPhone_, fragmentShaderPhone);
	glLinkProgram(shaderProgramPhone_);

	unsigned int shaderProgramGouraud_;
	shaderProgramGouraud_ = glCreateProgram();
	glAttachShader(shaderProgramGouraud_, vertexShaderGouraud);
	glAttachShader(shaderProgramGouraud_, fragmentShaderGouraud);
	glLinkProgram(shaderProgramGouraud_);

	unsigned int shaderProgramLight_;
	shaderProgramLight_ = glCreateProgram();
	glAttachShader(shaderProgramLight_, vertexShaderPhone);
	glAttachShader(shaderProgramLight_, fragmentShaderLight);
	glLinkProgram(shaderProgramLight_);

	// 链接后删除无用的着色器
	glDeleteShader(vertexShaderPhone);
	glDeleteShader(fragmentShaderPhone);
	glDeleteShader(vertexShaderGouraud);
	glDeleteShader(fragmentShaderGouraud);
	glDeleteShader(fragmentShaderLight);

	// 检查链接着色器出错
	glGetProgramiv(shaderProgramPhone_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramPhone_, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glGetProgramiv(shaderProgramGouraud_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramGouraud_, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glGetProgramiv(shaderProgramLight_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramLight_, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	shaderProgramPhone = shaderProgramPhone_;
	shaderProgramLight = shaderProgramLight_;
	shaderProgramGouraud = shaderProgramGouraud_;
}

unsigned int HW6::getShaderProgramPhone() {
	return shaderProgramPhone;
}

unsigned int HW6::getShaderProgramGouraud() {
	return shaderProgramGouraud;
}

void HW6::draw()
{
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HW6vertices), HW6vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
}

void HW6::Phong(Camera camera, bool dynamic, float ambientStrength, float diffuseStrength, float specularStrength, int Reflectivity, float x)
{
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0f);
	view = camera.GetViewMatrix();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(camera.getZoom()), (float)800 / (float)600, 0.1f, 100.0f);

	glUseProgram(shaderProgramPhone);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramPhone, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramPhone, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramPhone, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	
	glUniform1f(glGetUniformLocation(shaderProgramPhone, "ambientStrength"), ambientStrength);
	glUniform1f(glGetUniformLocation(shaderProgramPhone, "diffuseStrength"), diffuseStrength);
	glUniform1f(glGetUniformLocation(shaderProgramPhone, "specularStrength"), specularStrength);
	glUniform1i(glGetUniformLocation(shaderProgramPhone, "Reflectivity"), Reflectivity);
	glUniform3f(glGetUniformLocation(shaderProgramPhone, "lightColor"), 1.0f, 1.0f, 1.0f);
	if (dynamic)
		glUniform3f(glGetUniformLocation(shaderProgramPhone, "lightPos"), sin(glfwGetTime()) * 3, cos(glfwGetTime()) * 3, sin(glfwGetTime()) * 3);
	else
		glUniform3f(glGetUniformLocation(shaderProgramGouraud, "lightPos"), x, 3.0f, x);
	glUniform3f(glGetUniformLocation(shaderProgramPhone, "viewPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(lightVAO);

	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
	if (dynamic)
		model = glm::translate(model, glm::vec3(sin(glfwGetTime())*3, cos(glfwGetTime()) * 3, sin(glfwGetTime()) * 3));
	else 
		model = glm::translate(model, glm::vec3(x, 3.0, x));

	glUseProgram(shaderProgramLight);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void HW6::Gouraud(Camera camera, bool dynamic, float ambientStrength, float diffuseStrength, float specularStrength, int Reflectivity, float x)
{
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0f);
	view = camera.GetViewMatrix();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(camera.getZoom()), (float)800 / (float)600, 0.1f, 100.0f);

	glUseProgram(shaderProgramGouraud);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramGouraud, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramGouraud, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramGouraud, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(glGetUniformLocation(shaderProgramGouraud, "ambientStrength"), ambientStrength);
	glUniform1f(glGetUniformLocation(shaderProgramGouraud, "diffuseStrength"), diffuseStrength);
	glUniform1f(glGetUniformLocation(shaderProgramGouraud, "specularStrength"), specularStrength);
	glUniform1i(glGetUniformLocation(shaderProgramGouraud, "Reflectivity"), Reflectivity);
	glUniform3f(glGetUniformLocation(shaderProgramGouraud, "lightColor"), 1.0f, 1.0f, 1.0f);
	if (dynamic)
		glUniform3f(glGetUniformLocation(shaderProgramGouraud, "lightPos"), sin(glfwGetTime()) * 3, cos(glfwGetTime()) * 3, sin(glfwGetTime()) * 3);
	else
		glUniform3f(glGetUniformLocation(shaderProgramGouraud, "lightPos"), x, 3.0f, x);
	glUniform3f(glGetUniformLocation(shaderProgramGouraud, "viewPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(lightVAO);

	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
	if (dynamic)
		model = glm::translate(model, glm::vec3(sin(glfwGetTime()) * 3, cos(glfwGetTime()) * 3, sin(glfwGetTime()) * 3));
	else
		model = glm::translate(model, glm::vec3(x, 3.0, x)); // -2.1

	glUseProgram(shaderProgramLight);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}