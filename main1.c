#include <stdio.h>
#include "img.h"
#include "vector.h"


int main(){
    img_initparticles(50);
    int i;
    for(i=0; i<10; i++) {
        img_clear();
        img_plane();
        int n = create_vectors(50);
        img_moveparticles();
        img_write();
    }
    
    return 0;
}
