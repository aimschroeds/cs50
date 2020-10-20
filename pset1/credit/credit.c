#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

long get_credit_card_number(string prompt);

// Request user's credit card, determine if checksum is met and if yes, test to see if Amex, Visa or Mastercard
int main(void)
{

    long x = 0, last_digits, diff;

    int n, counter_luhn1 = 0, counter_luhn2 = 0, counter_luhn3 = 0, d1, d2, d3, d4 = 0;
    bool checksum;
    long credit_card = get_credit_card_number("What is your credit card number?\n");
    // Loop through all numbers in the provided credit card number
    for (int i = 1; i < 17; i++)
    {
        // Determine mod value to use and use it to isolate this iteration of loops final i number of digits in card number
        long to_mod_by_l = round(pow(10, i));
        last_digits = credit_card % to_mod_by_l;
        // Calculate difference between final i number of digits and previously identified numerator (from prior loop)
        diff = last_digits - x;
        // Determine digit at reverse i in the card number
        n = diff / (to_mod_by_l / 10);
        x = last_digits;
        // Capture first four digits in 16 digit string
        if (i > 12)
        {
            d4 = d3;
            d3 = d2;
            d2 = d1;
            d1 = n;
        }
        // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
        if (i % 2 == 0)
        {
            int n2 = n * 2;
            int sum_of_prod_n;
            if (n2 / 10 >= 1)
            {
                sum_of_prod_n = 1 + n2 % 10;
            }
            else
            {
                sum_of_prod_n = n2 % 10;
            }
            counter_luhn1 = counter_luhn1 + sum_of_prod_n;
        }
        // Calculate the sum of the digits that weren’t multiplied by 2.
        else
        {
            counter_luhn2 = counter_luhn2 + n;
        }

    }

    // Sum two counter_luhn sets and check that mod 10 == 0 to confirm checksum indicates a valid credit card number
    counter_luhn3 = counter_luhn1 + counter_luhn2;
    if (counter_luhn3 % 10 == 0)
    {
        checksum = true;
    }
    else
    {
        checksum = false;
    }
    // Test to ensure length of credit card number is within range
    if (credit_card < 3999999999990 || credit_card > 9999999999999999)
    {
        printf("INVALID\n");
    }
    // Test to see if the length is 16 chars and first digits are 51, 52, 53, 54 or 55 - indicative of Mastercard
    else if (checksum == true && d1 == 5 && (d2 == 1 || d2 == 2 || d2 == 3 || d2 == 4 || d2 == 5))
    {
        printf("MASTERCARD\n");
    }
    // Test to see if the length is 15 chars and first digits are 34 or 37 - indicative of AMEX
    else if (checksum == true && d1 == 0 && d2 == 3 && (d3 == 4 || d3 == 7))
    {
        printf("AMEX\n");
    }
    // Test to see if the length is 13 or 16 chars and first digit is 4 - indicative of VISA
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
    n = get_long("%s", prompt);
    return n;
}