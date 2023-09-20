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
	RT_Screen screen("./Shaders/rtSphere.vert", "./Shaders/rtSphere.frag");
	
	int i = 0;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		rec.Update(static_cast<float>(glfwGetTime()));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// update shader's camera
		screen.m_screenShader->use();
		screen.m_screenShader->setVec3("sph.pos", glm::vec3(0.f, 0.f, 0.f));
		screen.m_screenShader->setFloat("sph.r", 1.f);
		screen.m_screenShader->setVec3("lit.dir", glm::vec3(-1.f, -1.f, -1.f));
		screen.m_screenShader->setVec3("lit.color", glm::vec3(1.f, 1.f, 1.f));
		screen.m_screenShader->setVec3("lit.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		screen.m_screenShader->setVec3("cam.pos", cam.m_pos);
		screen.m_screenShader->setVec3("cam.front", cam.m_front);
		screen.m_screenShader->setVec3("cam.up", cam.m_up);
		screen.m_screenShader->setVec3("cam.right", cam.m_right);
		screen.m_screenShader->setFloat("cam.fov", cam.m_fov);
		screen.m_screenShader->setFloat("cam.near", cam.m_near);
		screen.m_screenShader->setFloat("cam.ratio", cam.m_ratio);
		screen.Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}