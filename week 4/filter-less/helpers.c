#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE img[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int avg = round((img[y][x].rgbtBlue + img[y][x].rgbtGreen + img[y][x].rgbtRed) / 3.0);
            img[y][x].rgbtRed = avg;
            img[y][x].rgbtGreen = avg;
            img[y][x].rgbtBlue = avg;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE img[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r = round(.393 * img[y][x].rgbtRed + .769 * img[y][x].rgbtGreen +
                          .189 * img[y][x].rgbtBlue);
            int g = round(.349 * img[y][x].rgbtRed + .686 * img[y][x].rgbtGreen +
                          .168 * img[y][x].rgbtBlue);
            int b = round(.272 * img[y][x].rgbtRed + .534 * img[y][x].rgbtGreen +
                          .131 * img[y][x].rgbtBlue);

            img[y][x].rgbtRed = r > 255 ? 255 : r;
            img[y][x].rgbtGreen = g > 255 ? 255 : g;
            img[y][x].rgbtBlue = b > 255 ? 255 : b;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE img[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            RGBTRIPLE temp = img[y][x];
            img[y][x] = img[y][width - x - 1];
            img[y][width - x - 1] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE img[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            tmp[y][x] = img[y][x];
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            float count = 0;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    int ny = y + dy, nx = x + dx;
                    if (ny >= 0 && ny < height && nx >= 0 && nx < width)
                    {
                        sumR += tmp[ny][nx].rgbtRed;
                        sumG += tmp[ny][nx].rgbtGreen;
                        sumB += tmp[ny][nx].rgbtBlue;
                        count++;
                    }
                }
            }

            img[y][x].rgbtRed = round(sumR / count);
            img[y][x].rgbtGreen = round(sumG / count);
            img[y][x].rgbtBlue = round(sumB / count);
        }
    }
}
