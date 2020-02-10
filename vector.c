#include "img.h"
#include "vector.h"
#include "math.h"

void showvector(struct vector v, struct coord xy){
   double r = sqrt(pow(v.x, 2) + pow(v.y, 2)); 
   struct color c = r2color(r); //struct color r2color(double r) 
   struct coord s  = {xy.x + VECTORSIZE * v.x / (r * 2), xy.y + VECTORSIZE * v.y /(r * 2) };
   struct coord e  = {xy.x - VECTORSIZE * v.x / (r * 2), xy.y - VECTORSIZE * v.y / (r * 2)};//cast??
   drawline(s, e, c);
}
