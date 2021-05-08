#include "Plant.h"
namespace Plant {
State Step(State P, Coeficient K, double input) {
  double uTemp = P.u;
  P.uOld = input;

  P.yOld = P.y;

  double A = K.a * P.u;
  double B = K.b * P.uOld;
  double C = 2 * K.c * P.yOld;
  double D = K.d * K.d;

  P.y = A + B - C - D;

  return P;
}
} // namespace Plant