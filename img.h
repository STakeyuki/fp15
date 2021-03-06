#ifndef IMG
#define IMG

#include "vector.h"
#define WIDTH 1200
#define HEIGHT 800

struct color {unsigned char r, g, b; };
struct coord {double x, y;}; 
struct pixel {int x; int y; struct color c;};

void img_clear(void);
void img_write(void);
void img_putpixel(struct color c, struct pixel);
void img_line(struct coord s, struct coord e, struct color c);
void img_triangle(struct coord v1, struct coord v2, struct coord v3, struct color c);
void img_vector(struct vector v, struct coord xy);
void img_circle(struct coord xy, double r, struct color c);
void img_plane();
void img_initparticles(unsigned int interval);
void img_moveparticles();
#endif
