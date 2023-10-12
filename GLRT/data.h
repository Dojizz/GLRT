#pragma once
#include "glm/gtc/type_ptr.hpp"
#include "RT_Screen.h"
#include "Camera.h"
#include "TimeRecord.h"

TimeRecord rec = TimeRecord();
Camera cam = Camera();
const float Camera::min_fov = 1.f;
const float Camera::max_fov = 45.f;
const float Camera::min_speed = 0.001f;
const float Camera::max_speed = 0.01f;

bool first_mouse = true;
unsigned int SCR_WIDTH = 1200;
unsigned int SCR_HEIGHT = 800;

float last_x = SCR_WIDTH / 2.0;
float last_y = SCR_HEIGHT / 2.0;

float mouse_sensitivity = 0.03f;
bool hide_cursor = false;

RenderBuffer render_buffer;