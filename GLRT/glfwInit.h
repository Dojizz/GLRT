#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Data.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float camera_move_length = static_cast<float>(2.5 * rec.GetDeltaTime());
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.Move(camera_move_length);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.Move(-camera_move_length);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.Move(camera_move_length, cam.GetRight() * (-camera_move_length));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.Move(camera_move_length, cam.GetRight() * (camera_move_length));
	if (hide_cursor)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	cam.SetWidthHeight(width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	render_buffer.Configuration(SCR_WIDTH, SCR_HEIGHT);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (!hide_cursor) {
		first_mouse = true;
		return;
	}
		
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (first_mouse)
	{
		last_x = xpos;
		last_y = ypos;
		first_mouse = false;
		return;
	}

	float xoffset = xpos - last_x;
	float yoffset = last_y - ypos;
	last_x = xpos;
	last_y = ypos;
	xoffset *= mouse_sensitivity;
	yoffset *= mouse_sensitivity;
	cam.UpdateYaw(xoffset);
	cam.UpdatePitch(yoffset);

	glm::vec3 front;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	front.x = cos(glm::radians(cam.GetYaw())) * cos(glm::radians(cam.GetPitch()));
	front.y = sin(glm::radians(cam.GetPitch()));
	front.z = sin(glm::radians(cam.GetYaw())) * cos(glm::radians(cam.GetPitch()));
	
	cam.SetFront(front);
	cam.SetRight(glm::cross(front, up));
	cam.SetUp(glm::cross(cam.GetRight(), cam.GetFront()));
	cam.ResetLoopNum();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		hide_cursor = true;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		hide_cursor = false;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.UpdateFov(yoffset);
}

GLFWwindow* GLFWInit() {
	// GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLRT", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	return window;
}