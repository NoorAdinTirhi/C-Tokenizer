#include <stdio.h>
#include <stdlib.h>

int main() {
    int x; 
    int y;
    int z;

    z = x << y;
    z = x >> y;
    z = x + y;
    z = x - y;
    z = x * y;
    z = x / y;
    z = x % y;
    
    x++;
    ++y;
    x--;
    --y;

    z = x & y;
    z = x | y;
    z = ~z;

    z += x;
    z -= y;
    z *= x;
    z /= y;
    z %= x;
    z &= y;
    z |= x;
    z ^= y;
    z <<= x;
    z >>= y;


    return 0;  
}