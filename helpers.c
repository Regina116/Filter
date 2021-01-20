#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float av;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            av = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = av;
            image[i][j].rgbtGreen = av;
            image[i][j].rgbtBlue = av;
        }
    }
    return;
}

// Sepia filter
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            if ((0.393 * r + 0.769 * g + 0.189 * b) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(0.393 * r + 0.769 * g + 0.189 * b);
            }

            if ((0.349 * r + 0.686 * g + 0.168 * b)>255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(0.349 * r + 0.686 * g + 0.168 * b);
            }

            if ((0.272 * r + 0.534 * g + 0.131 * b) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(0.272 * r + 0.534 * g + 0.131 * b);
            }
        }
    }
    return;
}

// Reflect image
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE list[1][1];
            list[0][0] = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = list[0][0];
        }
    }
    return;
}

// Blur filter
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumB;
    int sumG;
    int sumR;
    float counter;

    RGBTRIPLE temp[height][width]; //

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumB = 0;
            sumG = 0;
            sumR = 0;
            counter = 0.0;


            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int l = -1; l < 2; l++)
                {
                    if (i + l < 0 || i + l > width - 1)
                    {
                        continue;
                    }

                    sumB += image[j + k][i + l].rgbtBlue;
                    sumG += image[j + k][i + l].rgbtGreen;
                    sumR += image[j + k][i + l].rgbtRed;
                    counter++;
                }
            }

            // make average
            temp[j][i].rgbtBlue = round(sumB / counter);
            temp[j][i].rgbtGreen = round(sumG / counter);
            temp[j][i].rgbtRed = round(sumR / counter);
        }
    }

    // coping
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}