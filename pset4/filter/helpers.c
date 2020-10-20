#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each column / row of the images
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Assign existing rgb values to vars
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            // Calculate average of existing rgb values
            int g_val = round((r + g + b) / (float)3);

            // Assign pixel of image to avg for greyscale
            image[i][j].rgbtRed = g_val;
            image[i][j].rgbtGreen = g_val;
            image[i][j].rgbtBlue = g_val;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * r + 0.769 * g + 0.189 * b);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            int sepiaGreen = round(0.349 * r + 0.686 * g + 0.168 * b);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            int sepiaBlue = round(0.272 * r + 0.534 * g + 0.131 * b);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Set w_half to half the width of the image. If image has even length all pixels will be swopped with mirror equiv. If image is odd length, the mid column will remain the same.
    int w_half = floor(width / 2);

    // Iterate through all rows and first half (left hand side) of columns
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < w_half; j++)
        {
            // Set vars to the left hand RGB values in existing image
            int r_left = image[i][j].rgbtRed;
            int g_left = image[i][j].rgbtGreen;
            int b_left = image[i][j].rgbtBlue;

            // Set RGB of left hand pixels to the value of mirrored pixels
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            // Set RGB of right hand pixels to orig value of left hand ones
            image[i][width - j - 1].rgbtRed = r_left;
            image[i][width - j - 1].rgbtGreen = g_left;
            image[i][width - j - 1].rgbtBlue = b_left;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*blurred_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            float r_val = 0;
            float g_val = 0;
            float b_val = 0;
            // Iterate through the surrounding columns
            for (int k = i - 1; k <= i + 1; k++)
            {
                // Iterate through the surrounding rows
                for (int m = j - 1; m <= j + 1; m++)
                {
                    if (k > -1 && m > -1 && k < height && m < width)
                    {
                        counter = counter + 1;
                        r_val = r_val + image[k][m].rgbtRed;
                        g_val = g_val + image[k][m].rgbtGreen;
                        b_val = b_val + image[k][m].rgbtBlue;
                    }
                }
            }
            // Assign pixel of image to avg for greyscale
                blurred_image[i][j].rgbtRed = round(r_val / counter);
                blurred_image[i][j].rgbtGreen = round(g_val / counter);
                blurred_image[i][j].rgbtBlue = round(b_val / (float) counter);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurred_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurred_image[i][j].rgbtBlue;
        }
    }
    return;
}