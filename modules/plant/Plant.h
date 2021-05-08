#pragma once
namespace Plant {
struct State {
  double y;
  double yOld;
  double u;
  double uOld;
};

struct Coeficient {
  double a;
  double b;
  double c;
  double d;
};

State Step(State P, Coeficient K, double input);
} // namespace Plant