#pragma once

#include <cmath>

namespace waveform {

inline float sine(float pos)
{
  return std::sin(std::fmod(pos, 1) * 2 * M_PI);
}

inline float square(float pos)
{
  return std::fmod(pos, 1) < .5 ? 1 : -1;
}

inline float sawtooth(float pos)
{
  return 2 * std::fmod(pos, 1) - 1;
}

inline float triangle(float pos)
{
  return 4 * std::abs(std::fmod(pos - .25, 1) - .5) - 1;
}

inline float enable(float pos, float width)
{
  return std::fmod(pos, 1) < width;
}

}  // namespace waveform
