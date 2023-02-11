#pragma once

#include <lv2.h>
#include <cstdint>

class PluginHandle {
public:
  enum PortIndex { PORT_OUT_LEFT = 0, PORT_OUT_RIGHT = 1 };

private:
  float*   _outLeft;
  float*   _outRight;
  uint32_t _timeOffset;
  double   _rate;

public:
  PluginHandle(
      LV2_Descriptor const*     descriptor,
      double                    rate,
      char const*               bundle_path,
      LV2_Feature const* const* features);

  void connectPort(PortIndex port, void* data);
  void activate();
  void deactivate();
  void run(uint32_t nbSamples);
};
