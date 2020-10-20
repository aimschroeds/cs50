#include <stdio.h>

typedef char *string;

int main(void)
{
    int n = 50;
    int *p = &n;

    printf("%i\n", n);
    printf("%i\n", *&n);
    printf("%p\n", &n);
    printf("%p\n", p);
    printf("%i\n", *p);

    char *s = "EMMA";

    printf("%s\n", s);
    printf("%p\n", s);

    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);
    printf("%p\n", &s[4]);

    printf("%c\n", s[4]);

    printf("%c\n", *s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
    printf("%c\n", *(s+3));
    printf("%c\n", *(s+4));
}