#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string valid_key(int argc, string argv[]);
string encrypt(string ptext, string key);

int main(int argc, string argv[])
{
    // get valid key
    string key = valid_key(argc, argv);

    // exit if the key is invalid
    if (key == NULL)
    {
        return 1;
    }

    // prompt the user for plaintext
    string ptext = get_string("plaintext: ");

    // encrypt the plaintext
    string ctext = encrypt(ptext, key);

    // print ciphertext
    printf("ciphertext: %s\n", ctext);

    // free dynamically allocated memory
    free(key);
    free(ctext);

    // exit the program
    return 0;
}

// function to get valid key
string valid_key(int argc, string argv[])
{
    // with no or more than one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return NULL;
    }

    // the key is a single command-line argument
    string KEY = argv[1];

    // the key should contain 26 characters
    if (strlen(KEY) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return NULL;
    }

    // allocate memory for the uppercase key
    char *uppercaseKey = malloc(27 * sizeof(char)); // 26 characters + null terminator
    if (uppercaseKey == NULL)
    {
        exit(1);
    }

    // array to track seen letters (A-Z)
    bool seen[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        // the key should contain only alphabetic characters
        if(!isalpha(KEY[i]))
        {
            printf("Key must contain 26 characters.\n");
            free(uppercaseKey);
            return NULL;
        }

        // convert the key to case-insensitive
        char upperKey = toupper(KEY[i]);
        uppercaseKey[i] = upperKey;

        // map 'A'-'Z' to 0-25
        int index = upperKey - 'A';

        // check whether the key contains each letter exactly once
        if (seen[index])
        {
            // there's a duplicate
            printf("Key must contain 26 characters.\n");
            free(uppercaseKey);
            return NULL;
        }

        // mark the letter as seen
        seen[index] = true;
    }

    // add null terminator to the end of the key
    uppercaseKey[26] = '\0';

    // return the valid key
    return uppercaseKey;
}

// function to encrypt the plaintext with the valid key
string encrypt(string ptext, string key)
{
    int n = strlen(ptext);
    char *ctext = malloc((n + 1) * sizeof(char));
    if (ctext == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        char p = ptext[i];

        // substitute each alphabetical character with the key
        if (isalpha(p))
        {
            // case sensitive
            if (isupper(p))
            {
                ctext[i] = key[p - 'A'];
            }
            else
            {
                ctext[i] = tolower(key[p - 'a']);
            }
        }

        // non-alphabetical characters keep unchanged
        else
        {
            ctext[i] = p;
        }
    }

    ctext[n] = '\0';

    // return the ciphertext
    return ctext;
}
