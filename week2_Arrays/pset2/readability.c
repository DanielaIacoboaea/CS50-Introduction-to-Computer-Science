#include <stdio.h>
#include <string.h>

/* readability Coleman-Liau index:
index = 0.0588 * L - 0.296 * S - 15.8 */

int check_if_IsLetter(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
    {
        return 1;
    }
    return 0;
}

/* counting letters, words and sentences in separate functions*/

int count_letters(char text[1000], int n)
{
    int i, count = 0;
    for (i = 0; i < n; i++)
    {
        if (check_if_IsLetter(text[i]))
        {
            count++;
        }
    }

    return count;

}

int count_words(char text[1000], int n)
{
    int i = 0, count_words = 0;

    while (i < n)
    {
        if (text[i] == ' ')
        {
            count_words++;
        }else if (i == n-1)
        {
            count_words++;
        }
        i++;
    }

    return count_words;
}

int count_sentences(char text[1000], int n)
{
    int i = 0, count_sentences = 0;
    while (i < n)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_sentences++;
        }
        i++;
    }
    return count_sentences;
}

/* 65 letters / 14 words avg of 464.29 letters per 100 words.
14 words ... 65 letters
100 words .... x letters
x = 100 * 65 / 14 -> 464.28
*/

float find_average(int words_number, int to_find)
{
    float average;
    float word = words_number / 1.0;

    average = (100 * to_find) / word;

    return average;
}

/*find Coleman_Liau_index based on computed values*/

int Coleman_Liau_index(float letters_avg, float sencentes_avg)
{
    float calc_index, calc_index_fpart;
    int index;

    calc_index = 0.0588 * letters_avg - 0.296 * sencentes_avg - 15.8;

    calc_index_fpart = calc_index - (int) calc_index ;

    if (calc_index_fpart < 0.5)
    {
        index = (int) calc_index;

    }else
    {
         index = (int) calc_index + 1;
    }

    return index;
}

/*transform the index into grade*/

void print_grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }else if (index >= 16)
    {
        printf("Grade 16+\n");
    }else
    {
        printf("Grade %d\n", index);
    }
}

int main()
{
    char text[1000];
    int letters, words, sentences, index, i, n;
    float l, s;

    printf("enter text:\n");
    fgets(text, sizeof(text), stdin);

    n = strlen(text);

    letters = count_letters(text, n);
    words = count_words(text, n);
    sentences = count_sentences(text, n);

    l = find_average(words, letters);
    s = find_average(words, sentences);

    index = Coleman_Liau_index(l, s);

    print_grade(index);

    return 0;
}
