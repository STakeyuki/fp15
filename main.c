// animate1 --- create animation using img lib.
#include "img.h"
#include "vector.h"
#include <stdio.h>

int main(void) {
  struct color c1 = { 30, 255, 0 };
  struct coord a = { 1, 0.0 };
  struct coord b = { 0.0, 1 };
  struct coord c = { 0.0, 0.0 };
  struct coord a1 = { 0.0, 0.0 };
  struct coord b1 = { 350.0, 400.0 };
  img_clear();
  //img_plane();
  struct vector v = { a.x - b.x, a.y - b.y };
  struct vector v1 = { a1.x - b1.x, a1.y - b1.y };
  img_vector(v1, c);
  img_write();
  return 0;
}
