#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size = get_int("How big should your pyramid be?\n");
    printf("Height: %i \n", size);
    char brick = '#';
    for (int i = size; i >-1; i--)
    {
        for(int j = size - i; j < size; j++)
        {
            printf(" ");
        }
        for(int k = size - i; k > 0; k--)
        {
            printf("%c", brick);
        }
        printf("  ");
        for(int l = size - i; l > 0; l--)
        {
            printf("%c", brick);
        }

        printf("\n");

    }
}