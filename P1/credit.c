#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool checksum(long n, int digit);
void checkserver(long n, int digit);

int main(void)
{
    // user inputs card number
    long n = get_long("Number: ");

    // calculate how many digits the number has
    int digit = (int) log10(n) + 1;

    // checksum return true, card is valid
    if (checksum(n, digit))
    {
        // check card server
        checkserver(n, digit);
    }
    else
    {
        // checksum return false, card is invalid
        printf("INVALID\n");
    }

    return 0;
}

// checksum: Luhn’s Algorithm
bool checksum(long n, int digit)
{
    int sum = 0;

    // From second-to-last digit to get every other digit
    for (int i = 1; i < digit; i = i + 2)
    {
        int x = (n / (long) pow(10, i)) % 10;
        // Multiply by 2
        int y = x * 2;
        // add those products’ digits (NOT the products themselves) together
        sum += y / 10 + y % 10;
    }

    // Add the sum of the digits that weren’t multiplied by 2
    for (int i = 0; i < digit; i = i + 2)
    {
        sum += (n / (long) pow(10, i)) % 10;
    }

    // If the total’s last digit is 0, the number is valid.
    return sum % 10 == 0;
}

// check card server
void checkserver(long n, int digit)
{
    int x = n / (long) pow(10, digit - 2);

    // American Express uses 15-digit numbers
    if (digit == 15)
    {
        // All American Express numbers start with 34 or 37
        if (x == 34 || x == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        // Visa uses 13- and 16-digit numbers
        if (digit == 13)
        {
            // All Visa numbers start with 4
            if (x / 10 == 4)
            {
                printf("VISA\n");
            }
        }
        else
        {
            if (digit == 16)
            {
                // MasterCard uses 16-digit numbers
                // Most MasterCard numbers start with 51, 52, 53, 54, or 55
                if (x == 51 || x == 52 || x == 53 || x == 54 || x == 55)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    // Visa also uses 16-digit numbers
                    // All Visa numbers start with 4
                    if (x / 10 == 4)
                    {
                        printf("VISA\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}
