#include <stdio.h>
#include <stdlib.h>
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
  if(-WIDTH/2 => a.x  || a.x >= WIDTH/2 || -WIDTH/2 => a.x  || a.x >= WIDTH/2) { return; }
  buf[HEIGHT/2-a.y-1][a.x+HIGHT/2][0] = c.r;
  buf[HEIGHT/2-a.y-1][a.x+HIGHT/2][1] = c.g;
  buf[HEIGHT/2-a.y-1][a.x+HIGHT/2][2] = c.b;
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


