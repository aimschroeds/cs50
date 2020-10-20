// Build a brick Mario wall
#include <stdio.h>
#include <cs50.h>

int get_int_1_to_8(string prompt);

int main(void)
{
    int size = get_int_1_to_8("Height: ");

    // Loop through required rows of wall to add spaces, #s in right amount with even spacing in between
    char brick = '#';
    for (int i = size - 1; i > -1; i--)
    {
        // Print spaces at left of each row of blocks for correct alignment
        for (int j = size - i; j < size; j++)
        {
            printf(" ");
        }
        // Print # char for left hand row of bricks
        for (int k = size - i; k > 0; k--)
        {
            printf("%c", brick);
        }
        // Print space between row of bricks
        printf("  ");
        // Print # char for right hand row of bricks
        for (int l = size - i; l > 0; l--)
        {
            printf("%c", brick);
        }

        printf("\n");

    }
}

// Ensure user enters a positive integer between 1 and 8 (inclusive)
int get_int_1_to_8(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}