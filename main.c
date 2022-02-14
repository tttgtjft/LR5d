#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"

int main() {
    matrix a = getMemMatrix(5, 3);
    inputMatrix(&a);

    swapColumns(&a, 0, 2);
    outputMatrix(a);

    return 0;
}
