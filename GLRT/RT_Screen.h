#pragma once
#include "glad/glad.h"
#include <string>
#include "shader.h"

class RT_Screen {
private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	
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


// manage the frame buffer object
class ScreenFBO {
public:
	ScreenFBO() { }
	unsigned int m_framebuffer;
	unsigned int m_texture_color_buffer;
	unsigned int m_rbo;
	unsigned int m_width;
	unsigned int m_height;
	bool m_config = false;

	void Configuration(int scr_width, int scr_height) {
		if (m_config)
			Delete();
		// frame buffer
		glGenFramebuffers(1, &m_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		// bind texture
		glGenTextures(1, &m_texture_color_buffer);
		glBindTexture(GL_TEXTURE_2D, m_texture_color_buffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scr_width, scr_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_color_buffer, 0);
		// bind render buffer
		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR: framebuffer object uncomplete, rendering may be abnormal!" << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		m_config = true;
		m_width = scr_width;
		m_height = scr_height;
	}

	void Bind() {
		if (!m_config)
			return;
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	}

	void BindAsRead() {
		if (!m_config)
			return;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebuffer);
	}

	void BindAsDraw() {
		if (!m_config)
			return;
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);
	}


	void Unbind() {
		if (!m_config)
			return;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void BindAsTexture(int tex_unit = 0) {
		if (!m_config) {
			std::cout << "ERROR: framebuffer not configured, texture is empty!" << std::endl;
			return;
		}
		glActiveTexture(GL_TEXTURE0 + tex_unit);
		glBindTexture(GL_TEXTURE_2D, m_texture_color_buffer);
	}

	void Delete() {
		Unbind();
		glDeleteFramebuffers(1, &m_framebuffer);
		glDeleteTextures(1, &m_texture_color_buffer);
		m_config = false;
	}
};


// manage the three fbo during ray tracing rendering
class RenderBuffer {
private:
	ScreenFBO m_hist_fbo, m_pres_fbo, m_merge_fbo;
	unsigned int m_width;
	unsigned int m_height;
public:
	RenderBuffer() {}

	void Configuration(int scr_width, int scr_height) {
		// three fbo stay the same size
		m_hist_fbo.Configuration(scr_width, scr_height);
		m_pres_fbo.Configuration(scr_width, scr_height);
		m_merge_fbo.Configuration(scr_width, scr_height);
		m_width = scr_width;
		m_height = scr_height;
	}

	// use buffer screen to render new buffer & write to 0 texture
	void RenderNewFrame(RT_Screen& buffer_screen, RT_Screen& merge_screen, unsigned int loop_num) {
		m_pres_fbo.Bind();
		buffer_screen.Draw();
		m_pres_fbo.Unbind();
		m_pres_fbo.BindAsTexture(0);
		if (loop_num == 1) {
			m_pres_fbo.BindAsRead();
			m_hist_fbo.BindAsDraw();
			glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else {
			// use hist + pres, draw to merge_fbo
			m_hist_fbo.BindAsTexture(1);
			m_merge_fbo.Bind();
			// draw merge result to history fbo
			merge_screen.m_screenShader->use();
			merge_screen.m_screenShader->setInt("loop_num", loop_num);
			merge_screen.m_screenShader->setInt("pres_tex", 0);
			merge_screen.m_screenShader->setInt("hist_tex", 1);
			merge_screen.Draw();
			m_merge_fbo.Unbind();
			// copy merge_fbo to hist_fbo
			m_merge_fbo.BindAsRead();
			m_hist_fbo.BindAsDraw();
			glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		m_hist_fbo.BindAsTexture(0);
	}

};