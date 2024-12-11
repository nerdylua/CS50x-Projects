#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function to check if a string contains only digits
bool is_numeric(string str)
{
    for (int i = 0, len = strlen(str); i < len; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    // Ensure program is run with a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate that the key is numeric
    if (!is_numeric(argv[1]))
    {
        printf("Key must be a non-negative integer.\n");
        return 1;
    }

    // Convert the command-line argument to an integer (key)
    int key = atoi(argv[1]);

    // Ensure the key is non-negative
    if (key < 0)
    {
        printf("Key must be a non-negative integer.\n");
        return 1;
    }

    // Prompt user for the plaintext
    string plaintext = get_string("Text: ");

    // Begin output of the ciphertext
    printf("ciphertext: ");

    // Loop through each character in the plaintext
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        // Check if the character is alphabetic
        if (isalpha(plaintext[i]))
        {
            // Handle uppercase letters
            if (isupper(plaintext[i]))
            {
                char shifted_char = ((plaintext[i] - 'A' + key) % 26) + 'A';
                printf("%c", shifted_char);
            }
            // Handle lowercase letters
            else if (islower(plaintext[i]))
            {
                char shifted_char = ((plaintext[i] - 'a' + key) % 26) + 'a';
                printf("%c", shifted_char);
            }
        }
        // If the character is not alphabetic, print it as-is
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    // Print a newline after the ciphertext
    printf("\n");
    return 0;
}
