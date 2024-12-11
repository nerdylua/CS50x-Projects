#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Value assigned to each letter of the alphabet
int value[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Taking input
    string w1 = get_string("Player 1: ");
    string w2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(w1);
    int score2 = compute_score(w2);

    // Printing the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Score
    int score = 0;

    // Compute and return score for string
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += value[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += value[word[i] - 'a'];
        }
    }

    return score;
}
