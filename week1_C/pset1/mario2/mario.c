#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char sep = ' ';
    int h;
    int s;
    int z;
    
    do 
    {
        h = get_int("Pyramid height: \n");
    }while (h < 1 || h > 8);
    
    for (int y = 1; y <= h; y++)
    {
        //y=3
        //h=5
        //..###..###
        s = h - y; 
        
        for (int t = 1; t <= s; t++)
        {
            printf("%c", sep);
        }
   
        //..
        for (z = 1; z <= y; z++)
        {
            printf("#");
        }
        
        //..###
        printf("%c%c", sep, sep);
        
        //..###..
        for (z = 1; z <= y; z++)
        {
            printf("#");
        }
        //..###..###
        printf("\n");
    }
}
