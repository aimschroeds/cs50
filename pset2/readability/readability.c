#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

string get_text(string prompt);

// Request user's credit card, determine if checksum is met and if yes, test to see if Amex, Visa or Mastercard
int main(void)
{
    // Initializing word count to 1 as we will always miscount the final word as there is not space at end of sentence
    float word_count = 1, sentence_count = 0, letter_count = 0;
    string txt_str = get_string("Text: ");

    // Looping through each char in our string to identify letters, space (for words) and punctuation (!?.) (for sentences)
    for (int i = 0, len = strlen(txt_str); i < len; i++)
    {
        // Increment word count for any space found
        if (txt_str[i] == ' ')
        {
            word_count ++;
        }

        // Increment sentence count for any sentence ending punctuation found
        else if (txt_str[i] == '!' || txt_str[i] == '?' || txt_str[i] == '.')
        {
            sentence_count ++;
        }

        // Increment letter count for any alphabetic chars found
        else if 
        
        
        
        
        
        
        
        {
            letter_count ++;
        }
    }

    // Print letter, word and sentence counts
    printf("%.f letter(s)\n", letter_count);
    printf("%.f word(s)\n", word_count);
    printf("%.f sentence(s)\n", sentence_count);

    // Calculate letters per 100 words
    float let_100w = (letter_count / word_count) * 100;

    // Calculate sentences per 100 words
    float sen_100w = (sentence_count / word_count) * 100;

    // Calculate Coleman-Liau index
    float cl_index = 0.0588 * let_100w - 0.296 * sen_100w - 15.8;

    // Print grade level as determined by cl-index to screen
    if (cl_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cl_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", cl_index);
    }
}

// Prompt user to enter a text string
string get_text(string prompt)
{
    string s;
    s = get_string("%s", prompt);
    return s;
}