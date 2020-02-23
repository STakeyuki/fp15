#ifndef VECTOR
#define VECTOR

#define VECTORSIZE 25
#define VECTORNUMBER HEIGHT * WIDTH

struct vector{double x, y;};

struct vector f(double x, double y);
struct color r2color(double r);
void create_vectors(unsigned int interval);
double cross(struct vector v1, struct vector v2);

#endif
