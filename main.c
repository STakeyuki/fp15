// animate1 --- create animation using img lib.
#include "img.h"
#include "vector.h"
#include <stdio.h>

int main(void) {
  struct color c1 = { 30, 255, 0 };
  struct coord a = { -0.0, 0.0 };
  struct coord b = { 50.0, 80.0 };
  struct coord c = { -100.0, 0.0 };
  img_clear();
  img_triangle(a,b,c, c1);
  img_write();
  return 0;
}
