#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Number of buckets in the hash table
const unsigned int N = 10000;

// Hash function
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    size_t length = strlen(word);

    // Add ASCII value of character weighted by its position and word length
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value += (toupper(word[i]) * i + length);
    }

    // Use modulo to map the hash value to a bucket
    return hash_value % N;
}

int main()
{
    char word[101]; // Buffer to store input words (up to 100 characters)
    printf("Enter words to hash (type 'exit' to quit):\n");

    while (1)
    {
        printf("Word: ");
        scanf("%100s", word); // Read a word (up to 100 characters)

        // Exit the loop if the user types "exit"
        if (strcmp(word, "exit") == 0)
        {
            break;
        }

        // Hash the word and print the result
        unsigned int hash_value = hash(word);
        printf("Hash value for '%s': %u\n", word, hash_value);
    }

    printf("Exiting...\n");
    return 0;
}

