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

    // get number of letters
    int letters = count_letters(text);
    // printf("number of letters is: %i.\n", letters);

    // get number of words
    int words = count_words(text);
    // printf("number of words is: %i.\n", words);

    // get number of sentences
    int sentences = count_sentences(text);
    // printf("number of sentences is: %i.\n", sentences);

    // claculate the index
    int index = cl_index(letters, words, sentences);
    // printf("index: %i.\n", index);

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
    // initialize the number of words
    int n = 1;

    // get the number with a loop
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check whether a character is whitespace
        if (isspace(text[i]))
        {
            n++;
        }
    }

    // return the result
    return n;
}

// function to calculate sentences
int count_sentences(string text)
{
    // initialize the number of sentences
    int n = 0;

    // get the number with a loop
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // check whether a character is a mark to end a sentence like . ! or ?
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n++;
        }
    }

    // return the result
    return n;
}

// function to calculate the Coleman-Liau index
int cl_index(int letters, int words, int sentences)
{
    // L is the average number of letters per 100 words in the text
    // Cast values to float for accurate division
    float f_L = ((float) letters / words) * 100;
    // Round to the nearest whole number
    //int L = round(f_L);

    // S is the average number of sentences per 100 words in the text
    float f_S = ((float) sentences / words) * 100;
    //int S = round(f_S);

    // calculate index = 0.0588 * L - 0.296 * S - 15.8
    float f_n = 0.0588 * f_L - 0.296 * f_S - 15.8;
    int n = round(f_n);

    // return the result
    return n;
}
