#include "ILIGAME.h"

ILIGAME::VM::VM()
{
    // Make sure the screen starts black
    clearScreen(0);
}

void ILIGAME::VM::clearScreen(char color)
{
    // Force color in 0-15 range
    color &= 0b00001111;
    // Duplicate lower nibble to higher nibble to hold 2 pixels data
    color = color | (color << 4);
    for (int i = 0; i < GAME_HEIGHT; i++)
    {
        for (int o = 0; o < GAME_WIDTH / 2; o++)
        {
            // Thanks to duplicated nibble we can assign per byte
            gameScreen[i][o] = color;
        }
    }
}

void ILIGAME::VM::drawRect(char x1, char y1, char x2, char y2, char color, bool fill = false)
{
    // Force x1 and x2 in increasing order
    if (x2 < x1)
    {
        char temp = x2;
        x2 = x1;
        x1 = temp;
    }
    // Force y1 and y2 in increasing order
    if (y2 < y1)
    {
        char temp = y2;
        y2 = y1;
        y1 = temp;
    }
    // Force color to be in 0-15 range
    color = color & 0b00001111;

    // Cache a full color byte and high nibble color
    char colorHigh = color << 4;
    char colorByte = color | colorHigh;

    for (int row = y1; row < y2; row++)
    {
        if (fill || row == y1 || row == y2)
        {
            char col = x1;
            if (x1 % 2)
            {
                char *pixel = &gameScreen[y1][x1 / 2];
                *pixel = (*pixel & 0b11110000) & color;
                col++;
            }
            char bytesToWrite = (x2 - col + 1) / 2;
            for (int i = col / 2; i < col / 2 + bytesToWrite; i++)
            {
                gameScreen[y1][i] = colorByte;
            }
            if (!x2 % 2)
            {
                char *pixel = &gameScreen[y1][x1 / 2];
                *pixel = (*pixel & 0b00001111) & colorHigh;
            }
        }
        else
        {
            char *pixel = &gameScreen[row][x1 / 2];
            *pixel = (x1 % 2) ? (*pixel & 0b11110000) & color : (*pixel & 0b00001111) & colorHigh;
        }
    }
}

void ILIGAME::VM::drawRectRel(char x, char y, char w, char h, char color, bool fill = false)
{
    drawRect(x, y, x + w, y + h, color, fill);
}
