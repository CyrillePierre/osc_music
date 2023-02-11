#pragma once

#include <cmath>

class Counter {
public:
  using Value = float;

private:
  Value _value;
  Value _incr;

public:
  Counter(Value incr, Value initialValue = 0): _value(initialValue), _incr(incr) {}

  void update() { _value = std::fmod(_value + _incr, Value(1.)); }

  Value get() const { return _value; }

  operator Value() const { return _value; }
};
