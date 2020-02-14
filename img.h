#define WIDTH 1200
#define HEIGHT 800


struct color {unsigned char r, g, b; };
struct coord {double x, y;}; 
struct pixel {int x; int y; struct color c;};

void img_clear(void);
void img_write(void);
void img_putpixel(struct color c, struct pixel);
void img_line(struct coord s, struct coord e, struct color c);
void img_triangle(struct coord s, struct coord e, double hb, struct color c);
void img_fillcircle(struct color c, double x, double y, double r);

