#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate(string player);

int main(void)
{
    // prompt two players for one word each
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // calculate the score of each word
    int score1 = calculate(player1);
    int score2 = calculate(player2);

    // compare, print the winner and end
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

// function to calculate scores
int calculate(string player)
{
    // initialize the score
    int score = 0;

    // calculation loop
    for (int i = 0, len = strlen(player); i < len; i++)
    {
        if (isupper(player[i]))
        {
            score += POINTS[player[i] - 'A'];
        }
        else if (islower(player[i]))
        {
            score += POINTS[player[i] - 'a'];
        }
    }

    return score;
}
