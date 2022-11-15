#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct cypher_letter{
    char alphabeth_letter_up;
    char alphabeth_letter_low;
    char cypher_letter;

} cypher_letter;

void create_cypher(cypher_letter array[27], char key[27], int n)
{
    int i, ascii_code = 65;

    for (i = 0; i < n; i++)
    {
        array[i].alphabeth_letter_up = ascii_code + i;
        array[i].alphabeth_letter_low = (ascii_code + i) + 32;
        array[i].cypher_letter = key[i];
    }
}

char letter(char x, cypher_letter array[27], int n)
{
    int i;
    char cripted;

    if(isupper(x))
    {
        for (i = 0; i < n; i++)
        {
            if (array[i].alphabeth_letter_up == x)
            {
                if (isupper(array[i].cypher_letter))
                {
                    return array[i].cypher_letter;
                }else
                {
                    return (array[i].cypher_letter - 32);
                }
            }
        }
    }else{
        for (i = 0; i < n; i++)
        {
            if (array[i].alphabeth_letter_low == x)
            {
                if (islower(array[i].cypher_letter))
                {
                    return array[i].cypher_letter;
                }else
                {
                    return (array[i].cypher_letter + 32);
                }
            }
        }
    }
    return 0;
}

void create_ciphertext(char plaintext[256], char ciphertext[256], cypher_letter array[27], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if(isalpha(plaintext[i]))
        {
            ciphertext[i] = letter(plaintext[i], array, n);
        }else{
            ciphertext[i] = plaintext[i];
        }
    }
}

int main(int argc, string argv[])
{
    int i, n;

    char plaintext[256];
    char ciphertext[256];
    char key[27];
    cypher_letter array[27];
    char temp_argument[256];

    if (argc != 2)
    {
        printf("command-line argument missing");
        return 1;
    }
    n = strlen(argv[1]);

    if (n  != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
       
        if ((isalpha(argv[1][i]) == 0) || strchr(temp_argument, argv[1][i]) != NULL)
        {
            printf("Usage: ./substitution key");
            return 1;
        }else{
            temp_argument[i] = argv[1][i];
        }
    }

    strcpy(key, argv[1]);

    printf("plaintext: ");

    fgets(plaintext, sizeof(plaintext), stdin);

    create_cypher(array, key, n);

    create_ciphertext(plaintext, ciphertext,  array, 26);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
