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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

int main()
{
	GLFWwindow* window = GLFWInit();
	if (!window)
		return 1;
	RT_Screen buffer_screen("./Shaders/RayTracing.vert", "./Shaders/RayTracing.frag");
	RT_Screen screen("./Shaders/ScreenShader.vert", "./Shaders/ScreenShader.frag");

	// imgui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	// data initialize
	float radius = 1.f;
	float sphere_color[3] = { 0.5, 0.5, 0.5 };
	ScreenFBO fbo;
	fbo.Configuration(SCR_WIDTH, SCR_HEIGHT);
	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		rec.Update(static_cast<float>(glfwGetTime()));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// update shader's camera
		buffer_screen.m_screenShader->use();
		buffer_screen.m_screenShader->setVec3("sph.pos", glm::vec3(0.f, 0.f, 0.f));
		buffer_screen.m_screenShader->setFloat("sph.r", radius);
		buffer_screen.m_screenShader->setVec3("sphere_color", glm::vec3(sphere_color[0], sphere_color[1], sphere_color[2]));
		buffer_screen.m_screenShader->setVec3("lit.dir", glm::vec3(-1.f, -1.f, -1.f));
		buffer_screen.m_screenShader->setVec3("lit.color", glm::vec3(1.f, 1.f, 1.f));
		buffer_screen.m_screenShader->setVec3("lit.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		buffer_screen.m_screenShader->setVec3("cam.pos", cam.m_pos);
		buffer_screen.m_screenShader->setVec3("cam.front", cam.m_front);
		buffer_screen.m_screenShader->setVec3("cam.up", cam.m_up);
		buffer_screen.m_screenShader->setVec3("cam.right", cam.m_right);
		buffer_screen.m_screenShader->setFloat("cam.fov", cam.m_fov);
		buffer_screen.m_screenShader->setFloat("cam.near", cam.m_near);
		buffer_screen.m_screenShader->setFloat("cam.ratio", cam.m_ratio);
		// draw to fbo
		fbo.Bind();
		buffer_screen.Draw();
		fbo.Unbind();
		fbo.BindAsTexture();
		// draw to screen
		screen.m_screenShader->use();
		screen.m_screenShader->setInt("tex", 0);
		screen.Draw();

		ImGui::Begin("ImGUI window");
		ImGui::SliderFloat("radius", &radius, 0.1f, 10.f);
		ImGui::ColorEdit3("Color", sphere_color);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	fbo.Delete();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}