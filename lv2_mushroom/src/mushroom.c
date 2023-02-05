#include "mushroom.h"

#include "plugin_handle.h"

#include <math.h>

static float sine(PluginHandle* handle, float pos, float phase)
{
	return sinf(fmodf(pos / handle->rate + phase, 1) * 2 * M_PI);
}

static float square(PluginHandle* handle, float pos, float phase)
{
	return fmodf(pos / handle->rate + phase, 1) < .5 ? 1 : -1;
}

static float sawtooth(PluginHandle* handle, float pos, float phase)
{
	return 2 * fmodf(pos / handle->rate + phase, 1) - 1;
}

static float triangle(PluginHandle* handle, float pos, float phase)
{
	return 4 * fabs(fmodf(pos / handle->rate + phase - .25, 1) - .5) - 1;
}

void run(LV2_Handle instance, uint32_t n_samples)
{
	PluginHandle* handle = instance;
	float const   freq   = 70;

	for(uint32_t i = 0; i < n_samples; i++) {
		float pos            = freq * handle->time_offset;
		/* handle->out_left[i]  = .2 * sine(handle, 10 * pos, 0); */
		/* handle->out_right[i] = .2 * sine(handle, 10 * pos, 0.25); */
		/* handle->out_left[i]  = .2 * square(handle, pos, 0); */
		/* handle->out_right[i] = .2 * square(handle, pos*1.000, 0.25); */
		handle->out_left[i]  = .2 * triangle(handle, pos, 0);
		handle->out_right[i] = .2 * sine(handle, pos, 0);
		handle->time_offset++;
	}
}
