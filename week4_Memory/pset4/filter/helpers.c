#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            if (average - (int)average >= 0.5)
            {
                image[i][j].rgbtBlue = (int)average + 1;
                image[i][j].rgbtGreen = (int)average + 1;
                image[i][j].rgbtRed = (int)average + 1;
            }
            else
            {
                image[i][j].rgbtBlue = (int)average;
                image[i][j].rgbtGreen = (int)average;
                image[i][j].rgbtRed = (int)average;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE originalRed;
    BYTE originalGreen;
    BYTE originalBlue;

    float tempRed;
    float tempGreen;
    float tempBlue;
    int temp_r;
    int temp_g;
    int temp_b;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            tempBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            temp_b = round(tempBlue);

            if (temp_b > 255)
            {
                temp_b = 255;
            }
            image[i][j].rgbtBlue = temp_b;

            tempGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;

            temp_g = round(tempGreen);

            if (temp_g > 255)
            {
                temp_g = 255;
            }

            image[i][j].rgbtGreen = temp_g;

            tempRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;

            temp_r = round(tempRed);

            if (temp_r > 255)
            {
                temp_r = 255;
            }

            image[i][j].rgbtRed = temp_r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    int temp_i, temp_j, count;
    float temp_red, temp_blue, temp_green;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = 0;

            temp_red = 0;
            temp_blue = 0;
            temp_green = 0;

            for (temp_i = i - 1; temp_i <= i + 1; temp_i++)
            {
                for (temp_j = j - 1; temp_j <= j + 1; temp_j++)
                {
                    if (temp_i >= 0 && temp_i < height && temp_j >= 0 && temp_j < width)
                    {
                        temp_red = temp_red + temp_image[temp_i][temp_j].rgbtRed;
                        temp_blue = temp_blue + temp_image[temp_i][temp_j].rgbtBlue;
                        temp_green = temp_green + temp_image[temp_i][temp_j].rgbtGreen;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round(temp_red / count);
            image[i][j].rgbtBlue = round(temp_blue / count);
            image[i][j].rgbtGreen = round(temp_green / count);
        }
    }
    return;
}
