#include "Plant.h"

float Plant::Step(float input) {
  _old_input = _input;
  _old_output = _output;

  _input = input;
  _output = _a * _input + _b * _old_input - 2 * _c * _old_output - _d * _d;

  return _output;
}

float Plant::Output() {
    return _output;
}