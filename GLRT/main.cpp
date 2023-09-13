#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "Mesh.h"
#include "Model.h"
#include "glfwInit.h"
#include "data.h"
#include "RT_Screen.h"
#include "TimeRecord.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

int main()
{
	GLFWwindow* window = GLFWInit();
	if (!window)
		return 1;
	RT_Screen screen("./Shaders/rectShader.vert", "./Shaders/rectShader.frag");
	TimeRecord rec = TimeRecord();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		rec.Update(static_cast<float>(glfwGetTime()));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		screen.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}