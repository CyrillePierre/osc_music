#pragma once

#include <stdint.h>

typedef enum { PORT_OUTPUT = 0 } PortIndex;

typedef struct {
	float*   output;
	uint32_t time_offset;
	float    offset_to_angle;
} PluginHandle;
