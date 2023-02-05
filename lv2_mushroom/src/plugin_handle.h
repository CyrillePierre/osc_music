#pragma once

#include <stdint.h>

typedef enum { PORT_OUT_LEFT = 0, PORT_OUT_RIGHT = 1 } PortIndex;

typedef struct {
	float*   out_left;
	float*   out_right;
	uint32_t time_offset;
	double   rate;
} PluginHandle;
