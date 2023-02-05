#include "mushroom.h"
#include "plugin_handle.h"

#include <lv2.h>
#include <stdlib.h>

char const URI[] = "http://eseris.fr/lv2/mushroom";

/** Called by the host to create a new plugin instance. */
static LV2_Handle instantiate(
    const LV2_Descriptor*     descriptor,
    double                    rate,
    char const*               bundle_path,
    LV2_Feature const* const* features)
{
	PluginHandle* handle = calloc(1, sizeof(PluginHandle));

	handle->rate            = rate;
	return handle;
}

/** Called by the host to connect a particular port to a buffer. */
static void connect_port(LV2_Handle instance, uint32_t port, void* data)
{
	PluginHandle* handle = instance;

	switch((PortIndex) port) {
	case PORT_OUT_LEFT: handle->out_left = data; break;
	case PORT_OUT_RIGHT: handle->out_right = data; break;
	}
}

/** Called by the host to initialise and prepare the plugin instance for
 * running. */
static void activate(LV2_Handle instance)
{
	PluginHandle* handle = instance;

	handle->time_offset = 0;
}

/** Define a macro for converting a gain in dB to a coefficient. */
#define FROM_DB(g) ((g) > -90.0f ? powf(10.0f, (g) *0.05f) : 0.0f)

/** Called by the host after running the plugin. */
static void deactivate(LV2_Handle instance) {}

/** Destroy a plugin instance. */
static void cleanup(LV2_Handle instance)
{
	free(instance);
}

/** Returns any extension data supported by the plugin. */
static const void* extension_data(const char* uri)
{
	return NULL;
}

// clang-format off
static const LV2_Descriptor descriptor = {
	URI,
	instantiate,
	connect_port,
	activate,
	run,
	deactivate,
	cleanup,
	extension_data
};
// clang-format on

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
	return index == 0 ? &descriptor : NULL;
}
