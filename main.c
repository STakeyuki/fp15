// animate1 --- create animation using img lib.
#include "img.h"
#include "vector.h"
#include <stdio.h>

int main(void) {
  struct color c1 = { 30, 255, 0 };
  struct coord s = { -0.0, 0.0 };
  struct coord e = { 50.0, 80.0 };
  img_clear();
  img_triangle(s, e, 15.0, c1);
  img_write();
  return 0;
}
