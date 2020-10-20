#include <stdio.h>
#include <cs50.h>

// Request user's name and say hello
int main(void)
{
    string name = get_string("What is your name?\n");
    printf("hello, %s \n", name);
}