#include "tweens.h"

float easeOutQuad(float n) {
  return n*n;
}

float easeInQuad(float n) {
  return -n * (n-2);
}

float easeInOutQuad(float n) {
  return n < 0.5 ? 2*n*n : -.5 * ((2*n-1)*(2*n-3) - 1);
}
