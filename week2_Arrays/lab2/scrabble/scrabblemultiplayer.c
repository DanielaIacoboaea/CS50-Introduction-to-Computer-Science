#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    /*
    asd
    a
    s
    d
    s[i] ='c'
    */
    string player1 = get_string("Player1 scarbble word: \n");
    string player2 = get_string("PLayer2 scrabble word: \n");
    int scores[7] = {1, 2, 3, 4, 5, 8, 10};
    int sump1 = 0;
    int sump2 = 0;
    int n = strlen (player1);
    int m = strlen (player2);
    
    for (int i = 0; i < n; i++)
    {
        if (player1[i] == 'A'|| player1[i] == 'E' || player1[i] == 'I' || player1[i] == 'L' || player1[i] == 'N' || player1[i] == 'O' || player1[i] == 'R' || player1[i] == 'S' || player1[i] == 'T' || player1[i] == 'U')
        {
            sump1 = sump1 + 1;
        }
        else if (player1[i] == 'D' || player1[i] == 'G')
        {
            sump1 = sump1 + 2;
        }
        else if (player1[i] == 'B'|| player1[i] == 'C' || player1[i] == 'M' || player1[i] == 'P')
        {
            sump1 = sump1 + 3;
        }
        else if (player1[i] == 'F' || player1[i] == 'H' || player1[i] == 'V' || player1[i] == 'W' || player1[i] == 'Y')
        {
            sump1 = sump1 + 4;
        }
        else if (player1[i] == 'K')
        {
            sump1 = sump1 + 5;
        }
        else if (player1[i] == 'J' || player1[i] == 'X')
        {
            sump1 =  sump1 + 8;
        }
        else if (player1[i] == 'Q' || player1[i] == 'Z')
        {
            sump1 = sump1 + 10;
        }
    }
    
    for (int j = 0; j < m; j++){
        if (player2[j] == 'A'|| player2[j] == 'E' || player2[j] == 'I' || player2[j] == 'L' || player2[j] == 'N' || player2[j] == 'O' || player2[j] == 'R' || player2[j] == 'S' || player2[j] == 'T' || player2[j] == 'U')
        {
            sump2 = sump2 + 1;
        }
        else if (player2[j] == 'D' || player2[j] == 'G')
        {
            sump2 = sump2 + 2;
        }
        else if (player2[j] == 'B'|| player2[j] == 'C' || player2[j] == 'M' || player2[j] == 'P')
        {
            sump2 = sump2 + 3;
        }
        else if (player2[j] == 'F' || player2[j] == 'H' || player2[j] == 'V' || player2[j] == 'W' || player2[j] == 'Y')
        {
            sump2 = sump2 + 4;
        }
        else if (player2[j] == 'K')
        {
            sump2 = sump2 + 5;
        }
        else if (player2[j] == 'J' || player2[j] == 'X')
        {
            sump2 =  sump2 + 8;
        }
        else if (player2[j] == 'Q' || player2[j] == 'Z')
        {
            sump2 = sump2 + 10;
        }
    }
    
    printf("sum player1: %i\n", sump1);
    printf("sum player2: %i\n", sump2);
    
    if (sump1 > sump2)
    {
        printf("Winner: PLayer1\n");
    }
    else
    {
        printf("Winner: Player2\n");
    }
}
