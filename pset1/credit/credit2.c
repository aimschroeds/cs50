#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

long get_credit_card_number(string prompt);

// Request user's name and say hello
int main(void)
{
   long credit_card = get_credit_card_number("What is your credit card number?\n");
   int last_digit = credit_card % 10;
   printf("%i\n", last_digit);
   long remaining_cc;
   if (last_digit == 0)
   {
       remaining_cc = credit_card - 10;
   }
   else
   {
       remaining_cc = credit_card - last_digit;
   }
   printf("%li\n", remaining_cc);

    int last_digit2 = credit_card % 100;
   printf("%i\n", last_digit2);
   long remaining_cc2;
   if (last_digit == 0)
   {
       remaining_cc2 = credit_card - 10;
   }
   else
   {
       remaining_cc2 = credit_card - last_digit2;
   }
   printf("%li\n", remaining_cc2);

   int diff = last_digit2 - last_digit;
   int next = diff % 10;
   printf("diff: %i\n next: %i\n",diff,next);
}

// Ensure user enters a credit card number
long get_credit_card_number(string prompt)
{
    long n;
    n = get_long("%s", prompt);
    return n;
}