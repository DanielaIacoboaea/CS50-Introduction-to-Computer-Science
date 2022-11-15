#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x;
    
    //prompt user to enter value
    do 
    {
        x = get_int("Height: \n");
    }
    while (x < 1 || x > 8);
    int s;
    
    //y represents number of # and number of lines
    for (int y = 1; y <= x; y++)
    {
        s = x - y;
        
        //print blank spaces to move # in right for the pyramid
        for (int t = 1; t <= s; t++)
        {
            printf(" ");
        }
        
        //print # equal to number of lines (y)
        for (int z = 1; z <= y; z++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
