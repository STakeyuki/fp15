#include "img.h"
#include "vector.h"
#include "math.h"

double max_norm;

struct vector f(int x, int y){
    struct vector r = {x, y};
    return r;
}
struct color r2color(double r){
    int red, green;
    struct color c;
    if(r / max_norm < 0.5){
        c = {128,127 + 127 * max_norm ,0};
        return c;
    }
    if(r / max_norm >= 0.5){
        c = {127 + 127 * max_norm,128 ,0};
        return c;
    }
}

void create_vectors(unsigned int digit){
    int count = 0;
    for(int y = -HIGHT/2 + 1;y <= HEIGHT/2;y += digit, count++){
        for(int x = -HIGHT/2 + 1;x <= HEIGHT/2;x += digit){
            vectors[count] = f(x, y);
            double r = sqrt(pow(vectors[count].x, 2) + pow(vectors[count].y, 2)); 
            if(max_norm < r) max_norn = r;
        }
    }
}

void showvector(struct vector v, struct coord xy){
   double r = sqrt(pow(v.x, 2) + pow(v.y, 2)); 
   if (r < 0.001) {drawpoint(xy); return;}
   struct color c = r2color(r); //struct color r2color(double r) 
   struct coord s  = {xy.x + VECTORSIZE * v.x / (r * 2), xy.y + VECTORSIZE * v.y /(r * 2) };
   struct coord e  = {xy.x - VECTORSIZE * v.x / (r * 2), xy.y - VECTORSIZE * v.y / (r * 2)};//cast??
   drawline(s, e, c);
}

