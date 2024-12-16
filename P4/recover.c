#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open the memory card -> fopen
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open the file.\n");
        return 1;
    }

    // create a buffer for a block of data
    uint8_t buffer[512];

    // initialization
    FILE *img = NULL;
    char filename[8];
    int file_count = 0;

    // while there's still data left to read from the memory card -> fread
    while (fread(buffer, 1, 512, card) == 512)
    {
        // check whether it's a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if a JPEG is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // create JPEGs from the data -> sprintf
            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not open the file %s.\n", filename);
                fclose(card);
                return 1;
            }

            file_count++;
        }

        // if a JPEG file is open, write to it
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // fclose
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
