#pragma once

#include "counter.h"

#include <cstdint>
#include <lv2.h>

class PluginHandle {
public:
  enum PortIndex { PORT_OUT_LEFT = 0, PORT_OUT_RIGHT = 1 };

private:
  float*   _outLeft;
  float*   _outRight;
  double   _rate;
  float    _time{};

  Counter _lowPos;
  Counter _highPos;
  Counter _turnPos;

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
