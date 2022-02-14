#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"

int main() {
    matrix a = getMemMatrix(5, 2);
    inputMatrix(&a);

    swapRows(&a, 0, 2);
    outputMatrix(a);

    return 0;
}
