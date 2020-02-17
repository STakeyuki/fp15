#ifndef VECTOR
#define VECTOR

#include "img.h"
#define VECTORSIZE 50
#define VECTORNUMBER HEIGHT * WIDTH

struct vector{double x, y;};


struct vector f(double x, double y);

struct color r2color(double r);
int create_vectors(unsigned int digit);
double cross(struct vector v1, struct vector v2);

#endif
