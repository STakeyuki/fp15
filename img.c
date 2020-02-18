#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "img.h"

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];
#define PARTICLENUMBER HEIGHT * WIDTH
struct color particlecolor = {130,120,200};
static int pnum = 0;
static double particleradius = 3; 
struct coord particles[PARTICLENUMBER] = {{0,0}};

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

void img_clear(void) {
  int i, j;
  for(j = 0; j < HEIGHT; ++j) {
    for(i = 0; i < WIDTH; ++i) {
      buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 0;
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
  if(-WIDTH/2 > a.x  || a.x >= WIDTH/2 || -HEIGHT/2 > a.y  || a.y >= HEIGHT/2) { return; }
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
	struct pixel spoint = {(int)round(s.x), (int)round(s.y)};
	struct pixel epoint = {(int)round(e.x), (int)round(e.y)};
	double dx = abs(epoint.x - spoint.x);
	int sx = (spoint.x < epoint.x) ? 1 : -1;
	double dy = -absd(epoint.y - spoint.y);
	int sy = (spoint.y < epoint.y) ? 1 : -1;
	double err = dx + dy;
	while(1) {
		//printf("spoint %d %d epoint %d %d\n", spoint.x, spoint.y, epoint.x, epoint.y);
		img_putpixel(c, spoint); 
		if(spoint.x == epoint.x && spoint.y == epoint.y) break;
		double e2 = 2*err;
		if (e2 >= dy) {
			err += dy;
			if(spoint.x != epoint.x) spoint.x += sx;
		}
		if (e2 <= dx) {
			err += dx;
			if(spoint.y != epoint.y) spoint.y += sy;
		}
	}
}

void img_triangle(struct coord v1, struct coord v2, struct coord v3, struct color c) {
	struct vector vs1 = {v2.x - v1.x, v2.y - v1.y};
	struct vector vs2 = {v3.x - v1.x, v3.y - v1.y};
	int x,y;
	double maxX = max(v1.x, max(v2.x, v3.x));
	double minX = min(v1.x, min(v2.x, v3.x));
	double maxY = max(v1.y, max(v2.y, v3.y));
	double minY = min(v1.y, min(v2.y, v3.y));
	struct pixel p = {(int)round(minX), (int)round(minY), c};
	for (p.x = (int)round(minX) ; p.x <= (int)round(maxX); p.x++)
	{
	  for (p.y = (int)round(minY); p.y <= (int)round(maxY); p.y++)
	  {
	    struct vector q = {p.x - v1.x, p.y - v1.y};

	    double s = (double)cross(q, vs2) / cross(vs1, vs2);
	    double t = (double)cross(vs1, q) / cross(vs1, vs2);

	  if ( (s >= 0) && (t >= 0) && (s + t <= 1))
	    { /* inside triangle */
	      img_putpixel(c,p);
	    }

	  }
	}
}

void img_vector(struct vector v, struct coord xy){
   double r = sqrt(pow(v.x, 2) + pow(v.y, 2)); 
   if (r < 0.001) {return;}
   struct color c = r2color(r); //struct color r2color(double r) 
   printf("break %d %d %d %g\n", c.r, c.g, c.b, r);
   struct coord e  = {xy.x + VECTORSIZE * v.x / r, xy.y + VECTORSIZE * v.y /r};
   img_line(xy, e, c);
   struct coord b = { e.x - v.x*VECTORSIZE/(10*r), e.y - v.y*VECTORSIZE/(10*r) };
   struct coord a = { b.x - v.y*VECTORSIZE/(10*r), b.y + v.x*VECTORSIZE/(10*r) };
   struct coord d = { b.x + v.y*VECTORSIZE/(10*r), b.y - v.x*VECTORSIZE/(10*r) };
   img_triangle(e, a, d, c);
}

void img_plane() {
	struct coord x1 = {-WIDTH/2,0}, x2 = {WIDTH/2,0};
	struct coord y1 = {0,-HEIGHT/2}, y2 = {0,HEIGHT/2};
	struct color c = {255,255,255};	
	int i;
	struct color c2 = {0,102,102};	
	img_line(x1,x2,c);
	img_line(y1,y2,c);
	for(i = -HEIGHT/2; i <= HEIGHT/2; i+=50) {
		if(i==0) continue;		
		x1.y = x2.y = i;
		img_line(x1,x2,c2);
	}
	for(i = -WIDTH/2; i <= WIDTH/2; i+=50) {
		if(i==0) continue;		
		y1.x = y2.x = i;
		img_line(y1,y2,c2);
	}
	
}

void img_circle(struct coord xy, double r, struct color c) {
  int imin = (int)(xy.x - r - 1), imax = (int)(xy.x + r + 1);
  int jmin = (int)(xy.y - r - 1), jmax = (int)(xy.y + r + 1);
  int i, j;
  for(j = jmin; j <= jmax; ++j) {
    for(i = imin; i <= imax; ++i) {
	  struct pixel a = {i, j};
      if((xy.x-i)*(xy.x-i) + (xy.y-j)*(xy.y-j) <= r*r) { img_putpixel(c,a); }
    }
  }
}

void img_initparticles(unsigned int digit) {
	pnum = 0;
	for(int y = -HEIGHT/2 ;y < HEIGHT/2;y += digit){
        	for(int x = -WIDTH/2; x < WIDTH/2;x += digit){
			particles[pnum].x = x;
			particles[pnum].y = y;
			pnum++;
		}
	}
}

void img_moveparticles() {
	int i;
	for(i = 0; i < pnum; i++) {
		img_circle(particles[i], particleradius, particlecolor);
		particles[i].x += f(particles[i].x, particles[i].y).x/30;
		particles[i].y += f(particles[i].x, particles[i].y).y/30;
	}
}
