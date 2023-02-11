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
  PluginHandle* handle = new PluginHandle(descriptor, rate, bundle_path, features);
  return handle;
}

/** Called by the host to connect a particular port to a buffer. */
static void connect_port(LV2_Handle instance, uint32_t port, void* data)
{
  auto portIndex = static_cast<PluginHandle::PortIndex>(port);
  static_cast<PluginHandle*>(instance)->connectPort(portIndex, data);
}

/** Called by the host to initialise and prepare the plugin instance for
 * running. */
static void activate(LV2_Handle instance)
{
  static_cast<PluginHandle*>(instance)->activate();
}

static void run(LV2_Handle instance, uint32_t nbSamples)
{
  static_cast<PluginHandle*>(instance)->run(nbSamples);
}

/** Called by the host after running the plugin. */
static void deactivate(LV2_Handle instance)
{
  static_cast<PluginHandle*>(instance)->deactivate();
}

/** Destroy a plugin instance. */
static void cleanup(LV2_Handle instance)
{
  delete static_cast<PluginHandle*>(instance);
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
