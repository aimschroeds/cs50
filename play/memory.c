#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char *s = "emma";
    char *t = s;

    printf("%s\n", s);
    printf("%s\n", t);

    t[0] = toupper(t[0]);

    printf("%s\n", s);
    printf("%s\n", t);
}