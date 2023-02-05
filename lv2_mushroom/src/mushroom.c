#include "mushroom.h"

#include "plugin_handle.h"

#include <math.h>

void run(LV2_Handle instance, uint32_t n_samples)
{
	PluginHandle* handle = instance;
	float const   freq   = 440;

	for(uint32_t pos = 0; pos < n_samples; pos++) {
		handle->output[pos] = sinf(freq * handle->time_offset * handle->offset_to_angle);
		handle->time_offset++;
	}
}
