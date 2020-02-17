#include <stdio.h>
#include "img.h"
#include "vector.h"


int main(){
    struct coord p = { 100.0, 0.0 };
    struct color c1 = { 60, 60, 255 };
    int i;
    for(i=0; i<10; i++) {
        img_clear();
        img_plane();
        int n = create_vectors(50);
        
        img_circle(p,10,c1);
        p.x += f(p.x, p.y).x/50;
        p.y += f(p.x, p.y).y/50;
        img_write();
    }
    
    return 0;
}
