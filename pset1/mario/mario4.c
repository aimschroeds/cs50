#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size = get_int("How big should your pyramid be?\n");
    printf("Height: %i \n", size);
    char brick = '#';
    for (int i = 0; i < size; i++)
    {
        for(int j = size - i; j > 0; j--)
        {
            printf("%c", brick);
        }
        printf("  ");

        for(int k = size - i; k > 0; k--)
        {
            printf("%c", brick);
        }

        printf("\n");

    }
}