// animate1 --- create animation using img lib.
#include "img.h"
#include "vector.h"
#include <stdio.h>

int main(void) {
  struct color c1 = { 30, 255, 0 };
  struct coord a = { 50.0, 500.0 };
  struct coord b = { 500.0, 50.0 };
  struct coord c = { 0.0, 0.0 };
  img_clear();
  img_plane();
  struct vector v = { a.x - b.x, a.y - b.y };
  img_vector(v, c);
  img_write();
  return 0;
}
