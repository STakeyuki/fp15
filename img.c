#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];

void img_clear(void) {
  int i, j;
  for(j = 0; j < HEIGHT; ++j) {
    for(i = 0; i < WIDTH; ++i) {
      buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
    }
  }
}

void img_write(void) {
  sprintf(fname, "img%04d.ppm", ++filecnt);
  FILE *f = fopen(fname, "wb");
  if(f == NULL) { fprintf(stderr, "can't open %s\n", fname); exit(1); }
  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  fwrite(buf, sizeof(buf), 1, f);
  fclose(f);
}

void img_putpixel(struct color c, struct pixel a) {
  if(-WIDTH/2 > a.x  || a.x >= WIDTH/2 || -HEIGHT/2 >= a.y  || a.y >= HEIGHT/2) { return; }
  buf[HEIGHT/2-a.y-1][a.x+WIDTH/2][0] = c.r;
  buf[HEIGHT/2-a.y-1][a.x+WIDTH/2][1] = c.g;
  buf[HEIGHT/2-a.y-1][a.x+WIDTH/2][2] = c.b;
} 
int sign(double n) {
	return (n >= 0)? 1 : -1;
}
double absd(double n) {
	return (n >= 0)? n : -n;
}

void img_line(struct coord s, struct coord e, struct color c) {
	double dx = abs(e.x - s.x);
	int sx = (s.x < e.x) ? 1 : -1;
	double dy = -absd(e.y - s.y);
	int sy = (s.y < e.y) ? 1 : -1;
	double err = dx + dy;
	struct pixel spoint = {(int)round(s.x), (int)round(s.y)};
	struct pixel epoint = {(int)round(e.x), (int)round(e.y)};
	while(1) {
		img_putpixel(c, spoint); spoint.x++; img_putpixel(c, spoint); spoint.x++; img_putpixel(c, spoint); spoint.x -= 2;
		if(spoint.x == epoint.x && spoint.y == epoint.y) break;
		double e2 = 2*err;
		if (e2 >= dy) {
			err += dy;
			spoint.x += sx;
		}
		if (e2 <= dx) {
			err += dx;
			spoint.y += sy;
		}
	}
}

void img_triangle(struct coord s, struct coord e, double hb, struct color c) {
	int i;
	for(i = 0; i <= hb; i++) {
		s.x += i; s.y += i; e.x += i; e.y += i; img_line(s,e,c);
		s.x -= 2*i; s.y -= 2*i; e.x -= 2*i; e.y -= 2*i; img_line(s,e,c);
	}
}

void img_fillcircle(struct color c, double x, double y, double r) {
  int imin = (int)(x - r - 1), imax = (int)(x + r + 1);
  int jmin = (int)(y - r - 1), jmax = (int)(y + r + 1);
  int i, j;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
	  struct pixel a = {i, j};
      if((x-i)*(x-i) + (y-j)*(y-j) <= r*r) { img_putpixel(c,a); }
    }
  }
}


