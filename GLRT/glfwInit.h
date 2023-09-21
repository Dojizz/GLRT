#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "data.h"

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
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (!hide_cursor)
		return;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.03f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cam.m_yaw += xoffset;
	cam.m_pitch += yoffset;

	if (cam.m_pitch > 89.0f)
		cam.m_pitch = 89.0f;
	if (cam.m_pitch < -89.0f)
		cam.m_pitch = -89.0f;

	glm::vec3 front;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	front.x = cos(glm::radians(cam.m_yaw)) * cos(glm::radians(cam.m_pitch));
	front.y = sin(glm::radians(cam.m_pitch));
	front.z = sin(glm::radians(cam.m_yaw)) * cos(glm::radians(cam.m_pitch));
	
	cam.SetFront(front);
	cam.m_right = glm::normalize(glm::cross(front, up));
	cam.m_up = glm::normalize(glm::cross(cam.m_right, cam.m_front));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		hide_cursor = true;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		hide_cursor = false;
	std::cout << hide_cursor << std::endl;
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