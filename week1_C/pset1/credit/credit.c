#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // checksum total digits sum, n for number of digits, digit product;
    int digit;
    int n;
    int digit_product;
    long c;
    int checksum = 0;
    int prev_digit;
    bool correct_length;
    
    c = get_long("card number: \n");
    
    for (n = 0; c != 0; n++)
    {
        prev_digit = digit;
        digit = c % 10;
        c = c / 10;
   
        //check the second to last digit and add to sum for different cases
        if (n % 2 == 0)
        {
            checksum = checksum + digit;
        }
        else
        {
            //add individual digits and not digits product
            digit_product = 2 * digit;
            
            if (digit_product >= 10)
            {
                int digit2 = digit_product % 10;
                digit_product = digit_product / 10;
                checksum = checksum + digit2 + digit_product;
            }
            else
            {
                checksum = checksum + digit_product;
            }
        }
    }
    
    correct_length = n == 13 || n == 15 || n == 16;
    
    //use bool to prompt user for valid length
    //we now know that n=13 || 15 || 16; c = 0; and the checksum value;
    if (checksum % 10 == 0)
    {
        if (digit == 3 && (prev_digit == 7 || prev_digit == 4) && n == 15)
        {
            printf("AMEX\n");
        }
        else if (digit == 4 && (n == 16 || n == 13))
        {
            printf("VISA\n");
        }
        else if (digit == 5 && (prev_digit >= 1 && prev_digit <= 5) && n == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
