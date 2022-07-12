#include "ILIGAME.h"

#include <iostream>
#include <string.h>

ILIGAME::VM::VM()
{
	// Make sure the screen starts black
	clearScreen(0);

	resetFont();

	gameMemory = new char[256];
}

ILIGAME::VM::~VM()
{
	delete[] gameMemory;
}

void ILIGAME::VM::resetPallette()
{
	// TODO: Use pallette that is not pico-8 by default
}

void ILIGAME::VM::resetFont()
{
	for (unsigned char i = 'a'; i <= 'z'; i++)
	{
		font.charSize[i] = 3 << 4 | 5;
	}
	for (unsigned char i = '0'; i <= '9'; i++)
	{
		font.charSize[i] = 3 << 4 | 5;
	}

	font.charSize['\n'] = 5;
	font.charSize[' '] = 3 << 4 | 5;

	font.charMasks[' '] = {
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
	};

	font.charMasks['a'] = {
		0b11100000,
		0b10100000,
		0b11100000,
		0b10100000,
		0b10100000,
	};

	font.charMasks['b'] = {
		0b11000000,
		0b10100000,
		0b11100000,
		0b10100000,
		0b11000000,
	};

	font.charMasks['c'] = {
		0b11100000,
		0b10000000,
		0b10000000,
		0b10000000,
		0b11100000,
	};

	font.charMasks['d'] = {
		0b11000000,
		0b10100000,
		0b10100000,
		0b10100000,
		0b11000000,
	};

	font.charMasks['e'] = {
		0b11100000,
		0b10000000,
		0b11100000,
		0b10000000,
		0b11100000,
	};

	font.charMasks['f'] = {
		0b11100000,
		0b10000000,
		0b11100000,
		0b10000000,
		0b10000000,
	};

	font.charMasks['g'] = {
		0b11100000,
		0b10000000,
		0b10100000,
		0b10100000,
		0b11100000,
	};

	font.charMasks['h'] = {
		0b10100000,
		0b10100000,
		0b11100000,
		0b10100000,
		0b10100000,
	};

	font.charMasks['i'] = {
		0b11100000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b11100000,
	};

	font.charMasks['j'] = {
		0b01100000,
		0b00100000,
		0b00100000,
		0b10100000,
		0b11100000,
	};

	font.charMasks['k'] = {
		0b10100000,
		0b10100000,
		0b11000000,
		0b10100000,
		0b10100000,
	};

	font.charMasks['l'] = {
		0b10000000,
		0b10000000,
		0b10000000,
		0b10000000,
		0b11100000,
	};

	font.charMasks['m'] = {
		0b10100000,
		0b11100000,
		0b10100000,
		0b10100000,
		0b10100000,
	};

	font.charMasks['n'] = {
		0b10100000,
		0b11100000,
		0b11100000,
		0b10100000,
		0b10100000,
	};

	font.charMasks['o'] = {
		0b11100000,
		0b10100000,
		0b10100000,
		0b10100000,
		0b11100000,
	};

	font.charMasks['p'] = {
		0b11100000,
		0b10100000,
		0b11100000,
		0b10000000,
		0b10000000,
	};

	font.charMasks['q'] = {
		0b01100000,
		0b10100000,
		0b10100000,
		0b10100000,
		0b11100000,
	};

	font.charMasks['r'] = {
		0b11100000,
		0b10100000,
		0b11100000,
		0b11000000,
		0b10100000,
	};

	font.charMasks['s'] = {
		0b11100000,
		0b10000000,
		0b11100000,
		0b00100000,
		0b11100000,
	};

	font.charMasks['t'] = {
		0b11100000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b01000000,
	};

	font.charMasks['u'] = {
		0b10100000,
		0b10100000,
		0b10100000,
		0b10100000,
		0b11100000,
	};

	font.charMasks['v'] = {
		0b10100000,
		0b10100000,
		0b10100000,
		0b10100000,
		0b01000000,
	};

	font.charMasks['w'] = {
		0b10100000,
		0b10100000,
		0b10100000,
		0b11100000,
		0b10100000,
	};

	font.charMasks['x'] = {
		0b10100000,
		0b10100000,
		0b01000000,
		0b10100000,
		0b10100000,
	};

	font.charMasks['y'] = {
		0b10100000,
		0b10100000,
		0b01000000,
		0b01000000,
		0b01000000,
	};

	font.charMasks['z'] = {
		0b11100000,
		0b00100000,
		0b01000000,
		0b10000000,
		0b11100000,
	};

	font.charMasks['0'] = {
		0b01000000,
		0b10100000,
		0b10100000,
		0b10100000,
		0b01000000,
	};

	font.charMasks['1'] = {
		0b11000000,
		0b01000000,
		0b01000000,
		0b01000000,
		0b11100000,
	};

	font.charMasks['2'] = {
		0b11000000,
		0b00100000,
		0b01000000,
		0b10000000,
		0b11100000,
	};

	font.charMasks['3'] = {
		0b11000000,
		0b00100000,
		0b01100000,
		0b00100000,
		0b11000000,
	};

	font.charMasks['4'] = {
		0b00100000,
		0b01100000,
		0b10100000,
		0b11100000,
		0b00100000,
	};

	font.charMasks['5'] = {
		0b11100000,
		0b10000000,
		0b11000000,
		0b00100000,
		0b11000000,
	};

	font.charMasks['6'] = {
		0b01100000,
		0b10000000,
		0b11000000,
		0b10100000,
		0b01000000,
	};

	font.charMasks['7'] = {
		0b11100000,
		0b00100000,
		0b01000000,
		0b01000000,
		0b10000000,
	};

	font.charMasks['8'] = {
		0b01000000,
		0b10100000,
		0b01000000,
		0b10100000,
		0b01000000,
	};

	font.charMasks['9'] = {
		0b01000000,
		0b10100000,
		0b01100000,
		0b00100000,
		0b11000000,
	};
}

void ILIGAME::VM::init(){
	*(int*)gameMemory = 0;
}

bool ILIGAME::VM::tickUpdate()
{
	*(int*)gameMemory += 1;
	sprintf(gameMemory+4, "hello world!\nmousex: %u\nmousey: %u\nmouseactions: %u %u %u", mousePos.x, mousePos.y, (mouseActions & MouseActions::LEFT_CLICK), (mouseActions & MouseActions::RIGHT_CLICK), (mouseActions & MouseActions::MIDDLE_CLICK));
	return false;
}

bool ILIGAME::VM::tickDraw()
{
	ILIGAME::VM::drawRect(4, 4, GAME_WIDTH - 5, GAME_HEIGHT - 5, 7, true);
	ILIGAME::VM::drawRectRel(8, GAME_HEIGHT - 128 - 8, 128, 128, 0, true);
	ILIGAME::VM::drawRect(128 + 16 + 2, 1, GAME_WIDTH - 2, GAME_HEIGHT - 2, 0, false);
	ILIGAME::VM::drawRect(128 + 16 + 3, 2, GAME_WIDTH - 3, GAME_HEIGHT - 3, 7, true);
	ILIGAME::VM::drawText((char *)gameMemory + 4, 128 + 16 + 4, 3, 0);
	return false;
}

void ILIGAME::VM::clearScreen(unsigned char color)
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

void ILIGAME::VM::drawPixel(unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char *pixel = &gameScreen[y][x / 2];
	*pixel = x % 2 ? (*pixel & 0b11110000) | (color & 0b00001111) : (*pixel & 0b00001111) | color << 4;
}

void ILIGAME::VM::drawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color, bool fill = false)
{
	// Force x1 and x2 in increasing order
	if (x2 < x1)
	{
		unsigned char temp = x2;
		x2 = x1;
		x1 = temp;
	}
	// Force y1 and y2 in increasing order
	if (y2 < y1)
	{
		unsigned char temp = y2;
		y2 = y1;
		y1 = temp;
	}
	// Force color to be in 0-15 range
	color = color & 0b00001111;

	// Cache a full color byte and high nibble color
	unsigned char colorHigh = color << 4;
	unsigned char colorByte = color | colorHigh;

	for (int row = y1; row <= y2; row++)
	{
		if (fill || row == y1 || row == y2)
		{
			unsigned char col = x1;
			if (x1 % 2)
			{
				unsigned char *pixel = &gameScreen[row][x1 / 2];
				*pixel = (*pixel & 0b11110000) | color;
				col += 1;
			}
			unsigned char bytesToWrite = (x2 - col + 1) / 2;
			for (int i = col / 2; i < col / 2 + bytesToWrite; i++)
			{
				gameScreen[row][i] = colorByte;
			}
			if (x2 % 2 == 0)
			{
				unsigned char *pixel = &gameScreen[row][x2 / 2];
				*pixel = (*pixel & 0b00001111) | colorHigh;
			}
		}
		else
		{
			unsigned char *pixel = &gameScreen[row][x1 / 2];
			*pixel = (x1 % 2) ? (*pixel & 0b11110000) | color : (*pixel & 0b00001111) | colorHigh;
			pixel = &(gameScreen[row][x2 / 2]);
			*pixel = (x2 % 2) ? (*pixel & 0b11110000) | color : (*pixel & 0b00001111) | colorHigh;
		}
	}
}

void ILIGAME::VM::drawRectRel(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color, bool fill = false)
{
	drawRect(x, y, x + w - 1, y + h - 1, color, fill);
}

void ILIGAME::VM::drawText(const char *text, unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char carriage = x;
	for (unsigned int i = 0; text[i] != '\0'; i++)
	{
		switch (text[i])
		{
		case '\n':
			y += (font.charSize[text[i]] & 0b00001111) + 1;
			carriage = x;
			continue;
			break;
		case ' ':
			carriage += (font.charSize[text[i]] >> 4) + 1;
			continue;
			break;
		}
		FontChar fontChar = font.charMasks[text[i]];
		for (int row = 0; row < (font.charSize[text[i]] & 0b00001111); row++)
		{
			unsigned char rowMask = fontChar.mask[row];
			unsigned char bitMask = 0b10000000;
			for (int col = 0; col < font.charSize[text[i]] >> 4; col++)
			{
				if (rowMask & (bitMask >> col))
				{
					drawPixel(carriage + col, y + row, color);
				}
			}
		}
		carriage += (font.charSize[text[i]] >> 4) + 1;
	}
}
