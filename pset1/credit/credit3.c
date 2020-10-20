#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

long get_credit_card_number(string prompt);

// Request user's name and say hello
int main(void)
{
   long credit_card = get_credit_card_number("What is your credit card number?\n");
   for (int i = 1; i < 18; i++)
   {
        long to_mod_by_l = round(pow(10, i));
        printf("To Mod by last: %li\n", to_mod_by_l);
        int last_digit = credit_card % to_mod_by_l;
        printf("%i\n", last_digit);

        long to_mod_by_2l = round(pow(10, i + 1));
        printf("To Mod by 2last: %li\n", to_mod_by_2l);
        int last_digit2 = credit_card % to_mod_by_2l;
        printf("%i\n", last_digit2);
        int diff = last_digit2 - last_digit;
        int next = diff % 10;
        if (next == 0)
        {
            next = 1;
        }
        printf("diff: %i\nnext: %i\n",diff,next);
        int work_digit;
        if (i == 1)
        {
            work_digit = last_digit;
        }
        else
        {
            work_digit = next;
        }
        printf("work digit: %i\n", work_digit);
   }

}

// Ensure user enters a credit card number
long get_credit_card_number(string prompt)
{
    long n;
    n = get_long("%s", prompt);
    return n;
}