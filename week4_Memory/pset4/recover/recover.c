#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Usage: could not open file\n");
        return 1;
    }

    BYTE buffer[512];
    int count = 0;
    char image_name[50];
    FILE *image = NULL;

    while (fread(buffer, 512, 1, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (image != NULL)
            {
                fclose(image);
                count++;
            }
            sprintf(image_name, "%03i.jpg", count);
            image = fopen(image_name, "w");
        }
        if (image != NULL)
        {
            fwrite(buffer, 512, 1, image);
        }
    }

    fclose(input);
    fclose(image);
}