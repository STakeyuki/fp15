#include <stdio.h>
#include "img.h"
#include "vector.h"
#define N_FRAMES 180
#define VECTORS_INTERVAL 25
#define PARTICLES_INTERVAL 10

int main(){
    img_initparticles(10);
    int i;
    for(i=0; i<N_FRAMES; i++) {
        img_clear();
        img_plane();
        create_vectors(25);
        img_moveparticles();
        img_write();
    }
    
    return 0;
}
