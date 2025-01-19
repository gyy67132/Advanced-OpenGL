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

Camera camera(glm::vec3(0.0f, 0.0f, 55.0f));

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

	Model modelRock("./rock/rock.obj");
	Model model("./planet/planet.obj");
	
	Shader shader("./shader.vs", "./shader.fs");	
	Shader shaderInstance("./shader_instance.vs", "./shader.fs");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glm::mat4 projection = glm::perspective(45.0f, (float)800.0 / (float)600.0, (float)0.1, (float)100.0);
	
	unsigned int amount = 1000000;
	glm::mat4* modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime());
	float radius = 50.0f;
	float offset = 2.5f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model;
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));

		float scale = (rand() % 20) / 100.0f + 0.05f;
		model = glm::scale(model, glm::vec3(scale));

		float rotAngle = rand() % 360;
		model = glm::rotate(model, rotAngle, glm::vec3(0.4, 0.6, 0.8));

		modelMatrices[i] = model;
	}

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
	for (unsigned int i = 0; i < modelRock.meshes.size(); i++)
	{
		unsigned int VAO = modelRock.meshes[i].VAO;
		glBindVertexArray(VAO);

		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size * 2));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size * 3));
		
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
	

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
		glm::mat4 modelv = glm::translate(glm::mat4(1.0), glm::vec3(0.0, -3.0,0.0));
		modelv = glm::scale(modelv, glm::vec3(4.0, 4.0, 4.0));
		shader.setMat4("model", modelv);
		model.Draw(shader);

		shaderInstance.use();
		shaderInstance.setMat4("projection", projection);
		shaderInstance.setMat4("view", camera.GetViewMatrix());
		for (unsigned int i = 0; i < modelRock.meshes.size(); i++)
		{
			//shader.setMat4("model", modelMatrices[i]);
			//modelRock.Draw(shader);
			glBindVertexArray(modelRock.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, modelRock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
			glBindVertexArray(0);
		}
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