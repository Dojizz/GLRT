#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "RT_Screen.h"
#include "camera.h"
#include "TimeRecord.h"

TimeRecord rec = TimeRecord();
Camera cam = Camera();

bool firstMouse = true;
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

bool hide_cursor = false;