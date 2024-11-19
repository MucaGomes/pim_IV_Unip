#include <stdio.h>

void main() {
    int x = 0, y = 0;

    while (y < 5) {
        x = x + y;
        y++; // Incrementa y para evitar o loop infinito
    }

    printf("X = %d", x);
    return 0;
}
