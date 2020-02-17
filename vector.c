#include "vector.h"
#include "img.h"
#include <math.h>

double max_norm = 721.11;
struct vector vectors[VECTORNUMBER] = {{0,0}};

struct vector f(double x, double y){
    struct vector r = {x, y};
    return r;
}

struct color r2color(double r){
    int red, green;
    if(r / max_norm < 0.5){
        struct color c = {128,127 + 127 * max_norm ,0};
        return c;
    }
    if(r / max_norm >= 0.5){
        struct color c = {127 + 127 * max_norm,128 ,0};
        return c;
    }
}

int create_vectors(unsigned int digit){
    int count = 0;
    for(int y = -HEIGHT/2 ;y < HEIGHT/2;y += digit){
        for(int x = -WIDTH/2; x < WIDTH/2;x += digit, count++){
            if(count >= VECTORNUMBER){return;}
            struct vector v = f(x, y);
            vectors[count].x =  v.x;
            vectors[count].y =  v.y;
            double r = sqrt(pow(vectors[count].x, 2) + pow(vectors[count].y, 2)); 
            if(max_norm < r) max_norm = r;
        }
    }
    printf("hello %g\n", max_norm);
    count = 0;
    for(int y = -HEIGHT/2 ;y < HEIGHT/2;y += digit){
        for(int x = -WIDTH/2; x < WIDTH/2;x += digit, count++){
            printf("ha\n");
            if(count >= VECTORNUMBER){return;}
	    struct coord xy = {x, y};
            printf("%g %g\n", vectors[count].x, vectors[count].y);
            img_vector(vectors[count], xy);
	}
    }
    return count;
}

double cross(struct vector v1, struct vector v2) {
	return v1.x*v2.y - v1.y*v2.x;
}
