#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    // Open input file
    FILE *file = fopen(infile, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }
    int counter = 0;
    char image_name[64];
    // Initialize constant for number of bytes to read at a time
    int const size_chunk = 512;
    BYTE bytes[size_chunk];
    size_t block = fread(bytes, 1, size_chunk, file);
    // Ensure operations stop when reaching end of file
    while (block > 0)
    {
        // Check if first four bytes align with jpg expected bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
        {
            sprintf(image_name, "%03i.jpg", counter);
            counter++;
            FILE *image = fopen(image_name, "w");
            // Start writing first block to image file
            fwrite(&bytes, sizeof(bytes), 1, image);
            // Adjust block to continue reading next chunk
            block = fread(bytes, 1, size_chunk, file);
            // As long as end of file isn't reached, continue reading / writing to jpg
            while (block > 0)
            {
                // If new images is read in next chunk, close previous image file and break from while loop
                if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
                {
                    fclose(image);
                    break;
                }
                // Else continue writing to the image file and adjusting block to continue reading next chunk
                else
                {
                    fwrite(&bytes, sizeof(bytes), 1, image);
                    block = fread(bytes, 1, size_chunk, file);
                }
            }

        }
        // When searching for first jpg, if not immediately found, move to next chunk
        else
        {
            block = fread(bytes, 1, size_chunk, file);
        }
    }

    // Close file
    fclose(file);
    return 0;
}
