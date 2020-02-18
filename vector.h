#ifndef VECTOR
#define VECTOR

#define VECTORSIZE 25
#define VECTORNUMBER HEIGHT * WIDTH

struct vector{double x, y;};


struct vector f(double x, double y, int t);

struct color r2color(double r);
int create_vectors(unsigned int digit, int t);
double cross(struct vector v1, struct vector v2);

#endif
