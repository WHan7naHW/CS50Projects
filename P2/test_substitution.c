#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>



int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        if (strlen(key) == 26)
        {
            int n = 0;
            for (int i = 0; i < 26; i++)
            {
                if(isalpha(key[i]))
                {
                    n++;
                }
            }
            // key containing 26 alphabetic characters
            if (n == 26)
            {
                // accept a single command-line argument as the key
                printf("key is valid\n");
                //return 0;
            }
            else
            {
                // not containing each letter exactly once

                printf("Key must contain 26 characters.\n");
                //return 1;
            }
        }
        else
        {
            // not equal to 26
            printf("Key must contain 26 characters.\n");
            //return 1;
        }
    }
    else
    {
        // print error message
        printf("Usage: ./substitution key\n");
        //return 1;
    }

    // prompt the user for plaintext
    //.

    // print ciphertext
    //.

    // exit the program
    //return 0;
}
