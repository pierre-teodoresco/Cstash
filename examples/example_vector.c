#include "cstash/result.h"
#include "cstash/vector.h"

#include <stdio.h>

int main(void) {
    CsVector* vector = vector_create(sizeof(int), 10);

    int i = 0;
    for (; i < 10; i++) {
        if (vector_push(vector, &i) != CS_SUCCESS) {
            return 1;
        }
    }

    for (int j = 0; j < 10; j++) {
        printf("%d ", *((int*)vector_get(vector, j)));
    }
    printf("\n");

    vector_destroy(vector);
    return 0;
}
