#include "mandelbrot.hpp"

int isMandel(float a, float b, int iter) {
  int i;

  float re = 0;
  float im = 0;
  float temp;

  for (i = 0; i < iter; i++) {
    if (re * re + im * im > 4) break;
    temp = re * re - im * im + a;
    im = 2 * re * im + b;
    re = temp;
  }

  return i;
}
