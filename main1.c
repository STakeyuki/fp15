#include <stdio.h>
#include "img.h"
#include "vector.h"


int main(){
    create_vectors(50);
    for(int i = 0;i < 100;i++){
       printf("%d %d\n", vectors[i].x, vectors[i].y);
    }
    return 0;
}
