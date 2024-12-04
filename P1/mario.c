#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_grid(int height);

int main(void)
{
    int n = get_height();
    print_grid(n);
}

// get a positive integer between 1 and 8 as height
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_grid(int height)
{
    // print n lines
    for (int i = 0; i < height; i++)
    {
        // print n left spaces
        for (int j = height - i; j > 1; j--)
        {
            printf(" ");
        }

        // print n left hashes
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // print middle two spaces
        printf("  ");

        // print n right hashes
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // shift to the next line
        printf("\n");
    }
}
