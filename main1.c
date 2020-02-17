#include <stdio.h>
#include "img.h"
#include "vector.h"

extern struct vector vectors[VECTORNUMBER];

int main(){
    img_clear();
    img_plane();
    int n = create_vectors(50);
    img_write();
    return 0;
}
