#include <stdio.h>
#include "img.h"
#include "vector.h"

int main(){
    create_vectors(1);
    for(int i = 0;i <= VECTORNUMBER;i++){
       printf("%d %d\n", vectors[i].x ,vectors[i].y);
    }
    return 0;
}
