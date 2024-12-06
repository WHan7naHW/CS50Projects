#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int cl_index(int letters, int words, int sentences);

int main(void)
{
    // prompt user for text
    string text = get_string("Text: ");

    // get number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // claculate the index
    int index = cl_index(letters, words, sentences);

    // print the result: Before Grade 1, Grade X, or Grade 16+
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// function to count letters
int count_letters(string text)
{
    // initialize the number of letters
    int n = 0;

    // get the number with a loop
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check whether a character is alphabetical
        if (isalpha(text[i]))
        {
            n++;
        }
    }

    // return the number of letters
    return n;
}

// function to count words
int count_words(string text)
{
    int n = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check whether a character is whitespace
        if (isspace(text[i]))
        {
            n++;
        }
    }
    return n;
}

// function to calculate sentences
int count_sentences(string text)
{
    int n = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check whether a character is a mark to end a sentence as . ! or ?
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n++;
        }
    }
    return n;
}

// function to calculate the Coleman-Liau index
int cl_index(int letters, int words, int sentences)
{
    // L is the average number of letters per 100 words in the text
    // Cast values to float for accurate division
    float L = ((float) letters / words) * 100;

    // S is the average number of sentences per 100 words in the text
    float S = ((float) sentences / words) * 100;

    // calculate index = 0.0588 * L - 0.296 * S - 15.8
    float f_n = 0.0588 * L - 0.296 * S - 15.8;
    // Round to the nearest whole number
    int n = round(f_n);

    // return the result
    return n;
}
