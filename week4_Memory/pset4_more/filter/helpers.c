#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {{-1, -2, -1},
        {0, 0, 0},
                    {1, 2, 1}
    };

    RGBTRIPLE temp_image[height][width];
    int temp_i, temp_j, i, j, count_i, count_j;
    float temp_red, temp_blue, temp_green;
    float gx_red, gy_red, gx_blue, gy_blue, gx_green, gy_green;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            temp_red = 0;
            temp_blue = 0;
            temp_green = 0;

            count_i = 0;
            count_j = 0;

            gx_red = 0;
            gy_red = 0;

            gx_blue = 0;
            gy_blue = 0;

            gx_green = 0;
            gy_green = 0;

            for (temp_i = i - 1; temp_i <= i + 1; temp_i++)
            {
                count_j = 0;

                for (temp_j = j - 1; temp_j <= j + 1; temp_j++)
                {
                    if ((temp_i >= 0 && temp_i < height) && (temp_j >= 0 && temp_j < width))
                    {
                        gx_red += temp_image[temp_i][temp_j].rgbtRed * Gx[count_i][count_j];
                        gy_red += temp_image[temp_i][temp_j].rgbtRed * Gy[count_i][count_j];

                        gx_blue += temp_image[temp_i][temp_j].rgbtBlue * Gx[count_i][count_j];
                        gy_blue += temp_image[temp_i][temp_j].rgbtBlue * Gy[count_i][count_j];

                        gx_green += temp_image[temp_i][temp_j].rgbtGreen * Gx[count_i][count_j];
                        gy_green += temp_image[temp_i][temp_j].rgbtGreen * Gy[count_i][count_j];
                    }
                    else if (temp_i < 0 || temp_i >= height)
                    {
                        gx_red += 0;
                        gy_red += 0;

                        gx_blue += 0;
                        gy_blue += 0;

                        gx_green += 0;
                        gy_green += 0;
                    }
                    else if (temp_j < 0 || temp_j >= width)
                    {
                        gx_red += 0;
                        gy_red += 0;

                        gx_blue += 0;
                        gy_blue += 0;

                        gx_green += 0;
                        gy_green += 0;
                    }
                    count_j++;
                }
                count_i++;
            }

            temp_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            if (temp_red > 255)
            {
                temp_red = 255;
            }

            image[i][j].rgbtRed = temp_red;

            temp_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            if (temp_blue > 255)
            {
                temp_blue = 255;
            }

            image[i][j].rgbtBlue = temp_blue;

            temp_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            if (temp_green > 255)
            {
                temp_green = 255;
            }

            image[i][j].rgbtGreen = temp_green;
        }
    }

    return;
}
