#include <stdio.h>
#include <cs50.h>
#include <string.h>

int count_scrabble_points(string player_word);
bool string_contains(string letters, char letter_player_word);
string my_upper(string word);

int main(void)
{

    string player1 = get_string("Player 1: \n");
    string player2 = get_string("PLayer 2: \n");
    player1 = my_upper(player1);
    player2 = my_upper(player2);
    int points_player1 = count_scrabble_points(player1);
    int points_player2 = count_scrabble_points(player2);

    if (points_player1 == points_player2)
    {
        printf("Tie!\n");
    }
    else if (points_player1 > points_player2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}
//my_upper - convert to upperletters the player's word before counting the points of individual letters;
string my_upper(string word)
{
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] = word[i] - 32;
        }
    }
    //function declared as string, returns string;
    return word;
}

//check if letter appears in the player's word
bool string_contains(string letters, char letter_player_word)
{
  int n = strlen(letters);
  for (int j = 0; j < n; j++)
  {
      if (letters[j] == letter_player_word)
      {
          return true;
      }
  }
  return false;
}

//count points for each player;
int count_scrabble_points(string player_word)
{
    int n = strlen(player_word);
    int points = 0;
    for (int i = 0; i < n; i++)
    {
        if (string_contains("AEILNORSTU", player_word[i]) == true)
        {
            points = points + 1;
        }
        else if (string_contains("DG", player_word[i]) == true)
        {
            points = points + 2;
        }
        else if (string_contains("BCMP", player_word[i]) == true)
        {
            points = points + 3;
        }
        else if (string_contains("FHVWY", player_word[i]) == true)
        {
            points = points + 4;
        }
        else if (string_contains("K", player_word[i]) == true)
        {
            points = points + 5;
        }
        else if (string_contains("JX", player_word[i]) == true)
        {
            points =  points + 8;
        }
        else if (string_contains("QZ", player_word[i]) == true)
        {
            points = points + 10;
        }
    }
    return points;
}
