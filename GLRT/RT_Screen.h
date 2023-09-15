#pragma once
#include <string>
#include "shader.h"

class RT_Screen {
private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	
	//RT_Screen();

public:
	Shader* m_screenShader;
	RT_Screen(Shader* shader) {
		m_screenShader = shader;
		const float ScreenVertices[] = {
			// position in normalized space     // texture coord
			-1.f,	1.f,	0.f, 0.f, 1.f, // first triangle
			-1.f,	-1.f,	0.f, 0.f, 0.f,
			1.f,	1.f,	0.f, 1.f, 1.f,
			-1.f,	-1.f,	0.f, 0.f, 0.f, // second triangle
			1.f,	1.f,	0.f, 1.f, 1.f,
			1.f,	-1.f,	0.f, 1.f, 0.f
		};
		glGenBuffers(1, &m_VBO);
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenVertices), ScreenVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
	}
	RT_Screen(const char* vertexPath, const char* fragmentPath) {
		const float ScreenVertices[] = {
			// position in normalized space     // texture coord
			-1.f,	1.f,	0.f, 0.f, 1.f, // first triangle
			-1.f,	-1.f,	0.f, 0.f, 0.f,
			1.f,	1.f,	0.f, 1.f, 1.f,
			-1.f,	-1.f,	0.f, 0.f, 0.f, // second triangle
			1.f,	1.f,	0.f, 1.f, 1.f,
			1.f,	-1.f,	0.f, 1.f, 0.f
		};
		m_screenShader = new Shader(vertexPath, fragmentPath);
		glGenBuffers(1, &m_VBO);
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenVertices), ScreenVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
	};
	// TODO: this may cause leak, use smart pointer instead!
	void ChangeShader(Shader* shader) { m_screenShader = shader; } 
	void ChangeShader(const char* vertexPath, const char* fragmentPath) {
		m_screenShader = new Shader(vertexPath, fragmentPath);
	}

	void Draw() {
		glBindVertexArray(m_VAO);
		m_screenShader->use();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
};