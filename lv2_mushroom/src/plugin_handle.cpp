#include "plugin_handle.h"

#include "geometry.h"
#include "waveform.h"

PluginHandle::PluginHandle(
  LV2_Descriptor const*     descriptor,
  double                    rate,
  char const*               bundle_path,
  LV2_Feature const* const* features):
    _rate(rate), _lowPos(130 / rate), _highPos(16000 / rate), _turnPos(130 / rate * .995 / 3)
{
}

void PluginHandle::connectPort(PortIndex port, void* data)
{
  switch(port) {
  case PluginHandle::PORT_OUT_LEFT: _outLeft = static_cast<float*>(data); break;
  case PluginHandle::PORT_OUT_RIGHT: _outRight = static_cast<float*>(data); break;
  }
}

void PluginHandle::activate() {}

void PluginHandle::deactivate() {}

void PluginHandle::run(uint32_t nbSamples)
{
  using namespace waveform;

  for(uint32_t i = 0; i < nbSamples; i++) {
    float shape = .6 * sine(_lowPos) * enable(_lowPos + .25, .25) + .05 * enable(_lowPos, .75);
    float left  = .2 * sine(_highPos) * shape;
    float right = .05 * sine(_highPos + .25) * shape + .3 * sawtooth(_lowPos);
    left += .25 * (.5 * sawtooth(_lowPos) + .5) * sine(_turnPos);

    // rotate(left, right, _timeOffset / _rate);

    _outLeft[i]  = left;
    _outRight[i] = right;
    _lowPos.update();
    _highPos.update();
    _turnPos.update();
  }
}
