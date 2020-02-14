#define VECTORSIZE 10
#define VECTORNUMBER 200

struct vector{double x, y;}

struct vector vectors[VECTORNUMBER];

struct vector f(int x, int y);

struct color r2color(double r);
void create_vectors(unsigned int digit);
void showvector(struct vector v, struct coord xy);
