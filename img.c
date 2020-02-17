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

void img_triangle(struct coord v1, struct coord v2, struct coord v3, struct color c) {
	struct coord vs1 = {v2.x - v1.x, v2.y - v1.y};
	struct coord vs2 = {v3.x - v1.x, v3.y - v1.y};
	int x,y;
	int maxX = max(v1.x, max(v2.x, v3.x));
	int minX = min(v1.x, min(v2.x, v3.x));
	int maxY = max(v1.y, max(v2.y, v3.y));
	int minY = min(v1.y, min(v2.y, v3.y));
	struct pixel p = {minX, minY};
	for (; p.x <= maxX; p.x++)
	{
	  for (; p.y <= maxY; p.y++)
	  {
	   
	    struct vector q = {p.x - v1.x, y - v1.y};

	    double s = (double)crossProduct(q, vs2) / crossProduct(vs1, vs2);
	    double t = (double)crossProduct(vs1, q) / crossProduct(vs1, vs2);

	    if ( (s >= 0) && (t >= 0) && (s + t <= 1))
	    { /* inside triangle */
	      img_putpixel(c, p);
	    }
	  }
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


