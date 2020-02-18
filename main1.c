#include <stdio.h>
#include "img.h"
#include "vector.h"


int main(){
    //img_initparticles(5);
    int i;
    for(i=0; i<120; i++) {
	printf("%d  : ",i);
        img_clear();
        img_plane();
        int n = create_vectors(25,i);
        //img_moveparticles();
        img_write();
    }
    
    return 0;
}
