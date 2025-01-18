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
	//Model model("./Tree/Tree.obj");
	
	//Model model("./free-polestar-1/source/Polestar1_Final01.fbx");
	Shader shader("./shader.vs", "./shader.fs", "shader.gs");
	Camera camera;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.use();
		shader.setMat4("view", camera.getViewMatrix());
		glm::mat4 projection = glm::perspective(camera.getFov(), (float)800.0 / (float)600.0, (float)0.1, (float)100.0);
		shader.setMat4("projection", projection);
		glm::mat4 modelv = glm::translate(glm::mat4(1.0), glm::vec3(0.0,-10.0,0.0));
		shader.setMat4("model", modelv);
		shader.setFloat("time", glfwGetTime());
		model.Draw(shader);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}