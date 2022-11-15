#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int create_temp_key(int key)
{
    int temp_key;

    temp_key = key - 26;
    while (temp_key >= 26)
    {
        temp_key = temp_key - 26;
    }

    return temp_key;
}

char converted_letter(char x, int key)
{
    int temp_key, second_temp_key;

    if(isupper(x))
    {
        if ((int) x + key <= 90)
        {
            return (char)((int) x + key);
        }else {
            temp_key = key - (90 - (int) x);
            if((char)(64 + temp_key) <= 90 && (char)(64 + temp_key) >= 65)
            {
                return (char)(64 + temp_key);
            }else{
                temp_key = create_temp_key(key);
                if((int) x + temp_key <= 90)
                {
                    return (char)((int) x + temp_key);
                }else {
                    second_temp_key = temp_key - (90 - (int)x);
                    return (char)(64 + second_temp_key);
                }

            }

        }
    }else if (islower(x))
    {
        if ((int) x + key <= 122)
        {
            return (char)((int)x + key);
        }else {
            temp_key = key - (122 - (int) x);
            if((char)(96 + temp_key) <= 122 && (char)(96 + temp_key) >= 97)
            {
                return (char)(96 + temp_key);
            }else {
                temp_key = create_temp_key(key);
                if((int) x + temp_key <= 122)
                {
                    return (char)((int) x + temp_key);
                }else{
                    second_temp_key = temp_key - (122 - (int)x);
                    return (char)(96 + second_temp_key);
                }
            }

        }
    }
    return 0;
}


void cipher_word(char plaintext[], char ciphertext[], int n, int key)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if(isalpha(plaintext[i]))
        {
            ciphertext[i] = converted_letter(plaintext[i], key);
        }else
        {
            ciphertext[i] = plaintext[i];
        }
    }
}

int main(int argc, string argv[])
{
    int i, n, key, words_number;

    char plaintext[256];
    char ciphertext[256];

    if (argc != 2)
    {
        printf("command-line argument missing");
        return 1;
    }
    n = strlen(argv[1]);

    for (i = 0; i < n; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }

    key = atoi(argv[1]);

    printf("plaintext: ");

    fgets(plaintext, sizeof(plaintext), stdin);

    words_number = strlen(plaintext);

    cipher_word(plaintext, ciphertext, words_number, key);

    printf("ciphertext: %s", ciphertext);
    printf("\n");

    return 0;

}
