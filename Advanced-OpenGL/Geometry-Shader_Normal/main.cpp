#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/stb_image.h>

#pragma comment(lib, "../../lib/glew32.lib")
#pragma comment(lib, "../../lib/glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "../../lib/SOIL.lib")
#pragma comment(lib, "../../lib/assimp-vc143-mtd.lib")

#include <iostream>

#include "Model.h"
#include "Camera.h"

void processInput(GLFWwindow* window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 15.0f));

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "FAILED TO CREATE GLWINDOW" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	Model model("./nanosuit/nanosuit.obj");
	
	Shader shader("./shader.vs", "./shader.fs");
	Shader shaderNormal("./shaderNormal.vs", "./shaderNormal.fs", "shader.gs");
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glm::mat4 projection = glm::perspective(45.0f, (float)800.0 / (float)600.0, (float)0.1, (float)100.0);
	
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", camera.GetViewMatrix());
		glm::mat4 modelv = glm::translate(glm::mat4(1.0), glm::vec3(0.0, -10.0,0.0));
		shader.setMat4("model", modelv);
		shader.setFloat("time", glfwGetTime());
		model.Draw(shader);

		shaderNormal.use();
		shaderNormal.setMat4("view", camera.GetViewMatrix());
		shaderNormal.setMat4("model", modelv);
		shaderNormal.setMat4("projection", projection);
		model.Draw(shaderNormal);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}