#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

long get_credit_card_number(string prompt);

// Request user's name and say hello
int main(void)
{
   long credit_card = get_credit_card_number("What is your credit card number?\n");
   long x = 0;
   long last_digits;
   long diff;
   int n;
   int counter_luhn1 = 0;
   int counter_luhn2 = 0;
   int counter_luhn3 = 0;
   bool checksum;
   int d1, d2, d3, d4 = 0;

   for (int i = 1; i < 17; i++)
   {
        long to_mod_by_l = round(pow(10, i));
        last_digits = credit_card % to_mod_by_l;
        // printf("%li\n", last_digits);
        diff = last_digits - x;
        // printf("%li\n", diff);
        n = diff / (to_mod_by_l / 10);
        printf("N: %i\n----\n", n);
        x = last_digits;
        if(i > 12)
        {
            d4 = d3;
            d3 = d2;
            d2 = d1;
            d1 = n;
        }
        if (i % 2 == 0)
        {
            int n2 = n * 2;
            printf("n2: %i\n", n2);
            int sum_of_prod_n;
            if (n2 / 10 >= 1)
            {
                sum_of_prod_n = 1 + n2 % 10;
            }
            else
            {
                sum_of_prod_n = n2 % 10;
            }
            printf("SumofProdN: %i\n", sum_of_prod_n);
            counter_luhn1 = counter_luhn1 + sum_of_prod_n;
            printf("counterLuhn1: %i\n", counter_luhn1);
        }
        else
        {
            counter_luhn2 = counter_luhn2 + n;
        }

   }
    printf("d1-2: %i%i\n", d1, d2);
    counter_luhn3 = counter_luhn1 + counter_luhn2;
    printf("cl3: %i\n", counter_luhn3);
    if (counter_luhn3 % 10 == 0)
    {
        checksum = true;
    }
    else
    {
        checksum = false;
    }
    printf("first4digs: %i%i%i%i\n",d1,d2,d3,d4);
    if (checksum == true && d1 == 5 && (d2 == 1 || d2 == 2 || d2 == 3 || d2 == 4 || d2 == 5))
    {
        printf("MASTERCARD\n");
    }
    else if (checksum == true && d1 == 0 && d2 == 3 && (d3 == 4 || d3 == 7))
    {
        printf("AMEX\n");
    }
    else if (checksum == true && (d1 == 4 || (d1 == 0 && d2 == 0 && d3 == 0 && d4 == 4)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Ensure user enters a credit card number
long get_credit_card_number(string prompt)
{
    long n;
    do
    {
        n = get_long("%s", prompt);
    }
    while (n < 3999999999990 || n > 9999999999999999);
    return n;
}