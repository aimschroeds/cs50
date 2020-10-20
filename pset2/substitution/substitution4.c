// Program takes cypher as argument when called; checks if cypher is correct, then allows user to translate from non-cypher to cyphered plain text
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check if cypher has been passed as command line argument. Return usage instruction if incorrectly passed.
    if (argc == 2)
    {
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Pass cypher text to var and calculate it's length. Return error if not 26 chars long.
    string cypher_txt = argv[1];
    int cypher_len = strlen(cypher_txt);
    if (cypher_len == 26)
    {
    }
    else
    {
        printf("Your key does not contain 26 characters\n");
        return 1;
    }

    // Loop through each char in cypher
    for (int i = 0; i < cypher_len; i++)
        {
            // Check that each char is either lower case alpha or upper case alpha
            if ((cypher_txt[i] >= 'a' && cypher_txt[i] <= 'z') || (cypher_txt[i] >= 'A' && cypher_txt[i] <= 'Z'))
            {
                // Loop through each char in cypher a second time to determine that there are no duplicates
                for (int j = 0; j < cypher_len; j++)
                    {
                        // Skip comparing the char against itself
                        if (i == j)
                        {

                        }
                        // Compare the char against every other char in lowercase (to prevent upper/lower from misidentifying non matching chars)
                        else if (tolower(cypher_txt[i]) == tolower(cypher_txt[j]))
                        {
                            printf("Your key contains duplicate alphabetic characters\n");
                            return 1;
                        }
                        // Continue if all checks have been passed
                        else
                        {
                            continue;
                        }
                    }
            }
            else
            {
                printf("Your key contains non alphabetic characters\n");
                return 1;
            }
        }

    // Cypher passes all checks - we can proceed with allowing user to encrypt their plain text.
    string plain_txt = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, plain_txt_len = strlen(plain_txt); i < plain_txt_len; i++)
    {   
        
        if (plain_txt[i] >= 'a' && plain_txt[i] <= 'z')
        {
            printf("%c", tolower(cypher_txt[i]));
        }
        else if (plain_txt[i] >= 'A' && plain_txt[i] <= 'Z')
        {
            printf("%c", toupper(cypher_txt[i]));
        }
        else
        {
            printf("%c", plain_txt[i]);
        }
    }
    printf("\n");
    return 0;
}