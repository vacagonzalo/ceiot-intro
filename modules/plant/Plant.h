#pragma once
class Plant {
private:
  float _old_output;
  float _output;
  float _old_input;
  float _input;
  float _a;
  float _b;
  float _c;
  float _d;

public:
  Plant(float a, float b, float c, float d) : _a(a), _b(b), _c(c), _d(d) {
    _old_output = 0;
    _old_input = 0;
    _output = 0;
    _input = 0;
  }
  float Step(float input);
  float Output();
};