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

static float enable(PluginHandle* handle, float pos, float phase, float width)
{
	return fmodf(pos / handle->rate + phase, 1) < width;
}

void run(LV2_Handle instance, uint32_t n_samples)
{
	PluginHandle* handle = instance;
	float const   freq   = 100;

	for(uint32_t i = 0; i < n_samples; i++) {
		float pos   = freq * handle->time_offset;
		float pos2  = 100.01 * pos;
		float shape = .6 * sine(handle, pos, 0) * enable(handle, pos, .25, .25)
		              + .05 * enable(handle, pos, 0, .75);
		float left  = .2 * sine(handle, pos2, 0) * shape;
		float right = .05 * sine(handle, pos2, .25) * shape + .3 * sawtooth(handle, pos, 0);
		left += .1 * (.5 * sawtooth(handle, pos, 0) + .5) * sine(handle, pos * 1.007, .25);

		handle->out_left[i]  = left;
		handle->out_right[i] = right;
		handle->time_offset++;
	}
}
