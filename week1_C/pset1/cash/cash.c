#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float c;
    int x = 0;
    float r;
    
    do
    {
        c = get_float("Change owed: \n");
    }while (c < 0);
    
    c = c * 100;
    
    int ch = round(c);

    r = ch;
    for (x = 0; r != 0; x++)
    {
        r = r >= 25 ? r - 25
            : r >= 10 ? r - 10
            : r >= 5 ? r - 5
            : r >= 1 ? r - 1
            : 0;
    }
    
    printf("%i\n", x);
}
