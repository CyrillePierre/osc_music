#include "plugin_handle.h"

#include "geometry.h"
#include "waveform.h"

PluginHandle::PluginHandle(
  LV2_Descriptor const*     descriptor,
  double                    rate,
  char const*               bundle_path,
  LV2_Feature const* const* features):
    _rate(rate)
{
}

void PluginHandle::connectPort(PortIndex port, void* data)
{
  switch(port) {
  case PluginHandle::PORT_OUT_LEFT: _outLeft = static_cast<float*>(data); break;
  case PluginHandle::PORT_OUT_RIGHT: _outRight = static_cast<float*>(data); break;
  }
}

void PluginHandle::activate()
{
  _timeOffset = 0;
}

void PluginHandle::deactivate() {}

void PluginHandle::run(uint32_t nbSamples)
{
  using namespace waveform;

  for(uint32_t i = 0; i < nbSamples; i++) {
    float pos   = 130 * _timeOffset / _rate;
    float pos2  = 10000 * _timeOffset / _rate;
    float shape = .6 * sine(pos) * enable(pos + .25, .25) + .05 * enable(pos, .75);
    float left  = .2 * sine(pos2) * shape;
    float right = .05 * sine(pos2 + .25) * shape + .3 * sawtooth(pos);
    left += .25 * (.5 * sawtooth(pos) + .5) * sine(pos * .995 / 3 + .25);

    // rotate(left, right, _timeOffset / _rate);

    _outLeft[i]  = left;
    _outRight[i] = right;
    _timeOffset++;
  }
}
