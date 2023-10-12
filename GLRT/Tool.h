#pragma once
// generate random number
#include "time.h"
#include <stdlib.h>

void CPURandomInit() {
	srand(time(NULL));
}

float GetCPURandom() {
	return (float)rand() / (RAND_MAX + 1.0);
}