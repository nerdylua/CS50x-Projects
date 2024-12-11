#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for input text
    string input = get_string("Text: ");

    // Count letters, words, and sentences
    int letter_count = count_letters(input);
    int word_count = count_words(input);
    int sentence_count = count_sentences(input);

    // Calculate averages per 100 words
    float avg_letters = (100.0 / word_count) * letter_count;
    float avg_sentences = (100.0 / word_count) * sentence_count;

    // Calculate readability score using Coleman-Liau index
    int grade_level = round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8);

    // Print the readability grade
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}

// Count alphabetic characters in the text
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Count words in the text (words are separated by spaces)
int count_words(string text)
{
    int count = 1; // Start at 1 to count the first word
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

// Count sentences in the text (sentences end with ., !, or ?)
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
