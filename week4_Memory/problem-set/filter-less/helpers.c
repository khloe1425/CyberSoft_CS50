#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (int)((image[i][j].rgbtBlue + (image[i][j]).rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = fmin(255, (int)(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue + 0.5));
            image[i][j].rgbtGreen = fmin(255, (int)(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue + 0.5));
            image[i][j].rgbtBlue = fmin(255, (int)(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue + 0.5));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            float counter = 0.00;

            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    int currentA = i + a;
                    int currentB = j + b;

                    if (currentA < 0 || currentA > (height - 1) || currentB < 0 || currentB > (width - 1))
                    {
                        continue;
                    }

                    totalRed += image[currentA][currentB].rgbtRed;
                    totalGreen += image[currentA][currentB].rgbtGreen;
                    totalBlue += image[currentA][currentB].rgbtBlue;

                    counter++;
                }
            }

            temp[i][j].rgbtRed = round(totalRed / counter);
            temp[i][j].rgbtGreen = round(totalGreen / counter);
            temp[i][j].rgbtBlue = round(totalBlue / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
