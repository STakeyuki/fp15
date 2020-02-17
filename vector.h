#ifndef VECTOR
#define VECTOR

#include "img.h"
#define VECTORSIZE 10
#define VECTORNUMBER 200

double max_norm;

struct vector{double x, y;};

struct vector vectors[VECTORNUMBER];

struct vector f(int x, int y);

struct color r2color(double r);
void create_vectors(unsigned int digit);
void showvector(struct vector v, struct coord xy);
double cross(struct vector v1, struct vector v2);

#endif
