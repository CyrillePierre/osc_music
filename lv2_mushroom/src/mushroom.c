#include "mushroom.h"

#include "plugin_handle.h"

#include <math.h>

static float sine(float pos)
{
	return sinf(fmodf(pos, 1) * 2 * M_PI);
}

static float square(float pos)
{
	return fmodf(pos, 1) < .5 ? 1 : -1;
}

static float sawtooth(float pos)
{
	return 2 * fmodf(pos, 1) - 1;
}

static float triangle(float pos)
{
	return 4 * fabs(fmodf(pos - .25, 1) - .5) - 1;
}

static float enable(float pos, float width)
{
	return fmodf(pos, 1) < width;
}

void run(LV2_Handle instance, uint32_t n_samples)
{
	PluginHandle* handle = instance;

	for(uint32_t i = 0; i < n_samples; i++) {
		float pos   = 130 * handle->time_offset / handle->rate;
		float pos2  = 10000 * handle->time_offset / handle->rate;
		float shape = .6 * sine(pos) * enable(pos + .25, .25) + .05 * enable(pos, .75);
		float left  = .2 * sine(pos2) * shape;
		float right = .05 * sine(pos2 + .25) * shape + .3 * sawtooth(pos);
		left += .25 * (.5 * sawtooth(pos) + .5) * sine(pos * .995 / 3 + .25);

		handle->out_left[i]  = left;
		handle->out_right[i] = right;
		handle->time_offset++;
	}
}
