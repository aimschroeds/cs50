#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    float rl = (27 + 28 + 28) / (float) 3;
    printf("%f\n", rl);
    int r = round(rl);
    printf("%i\n", r);
    int r0 = roundf((27 + 28 + 28) / 3);
    printf("%i\n", r0);
    int r1 = rint((27 + 28 + 28) / 3);
    printf("%i\n", r1);
    int r2 = rintf((27 + 28 + 28) / 3);
    printf("%i\n", r2);
    int r3 = lround((27 + 28 + 28) / 3);
    printf("%i\n", r3);
}