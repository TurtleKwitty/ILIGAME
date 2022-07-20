#include "ILIGAME.h"

#include <iostream>
#include <string.h>

ILIGAME::VM::VM()
{
	// Make sure the screen starts black
	clearScreen(0);

	gameMemory = new char[65536];
}

ILIGAME::VM::~VM()
{
	delete[] gameMemory;
}

void ILIGAME::VM::flip(){
	//Move mouseActions to last frame
	mouseActions = (mouseActions << 4) | (mouseActions & 0b00001111);
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

	font.charSize['\n'] = 3 << 4 | 5;
	font.charSize[' '] = 3 << 4 | 5;

	for(int i = 0; i < 256; i++){
		font.charMasks[i] = {
			0b11111110,
			0b10000010,
			0b10000010,
			0b10000010,
			0b10000010,
			0b10000010,
			0b11111110,
			0b00000000
		};
	}

	font.charMasks[' '] = {
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
	};

	font.charMasks['\n'] = {
		0b11111000,
		0b10111000,
		0b10111000,
		0b10100000,
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

	font.charMasks[255] = {
		0b01000001,
		0b10100001,
		0b01100001,
		0b00100001,
		0b11000001,
	};
}

bool ILIGAME::VM::tickInit(){
	*gameMemory = 'b';

	char* fontFileData = nullptr;
	unsigned int fontFileSize = readFile("resources/font.bin", fontFileData);
	if(fontFileData){
		Font* customFont = (Font*)(gameMemory + 8);
		memcpy(customFont, fontFileData, sizeof(Font));
		memcpy(&font, fontFileData, sizeof(Font));
		delete[] fontFileData;
	} else {
		resetFont();

		Font* customFont = (Font*)(gameMemory + 8);
		memcpy(customFont, &font, sizeof(Font));
	}

	return false;
}

bool ILIGAME::VM::tickUpdate()
{
	if((mouseActions & (ILIGAME::MouseActions::LEFT_CLICK | ILIGAME::MouseActions::LEFT_CLICK_LAST)) == ILIGAME::MouseActions::LEFT_CLICK_LAST){
		if(!(mousePos.x < 8 || mousePos.x > 8 + 8*9 || mousePos.y < 8 || mousePos.y > 8 + 8*9)){
			char clickX = (mousePos.x - 8)/9;
			char clickY = (mousePos.y - 8)/9;
			Font* customFont = (Font*)(gameMemory + 8);
			FontChar* currentChar = &customFont->charMasks[*gameMemory];
			
			currentChar->mask[clickY] ^= (0b10000000 >> clickX);

			//Unsaved changes
			*(gameMemory + 1) = true;
		} 
		else if(!(mousePos.x < 8+1+8*9 || mousePos.x > 8+1+8*9 + 8 || mousePos.y < 8+1+1*9 || mousePos.y > 8+1+1*9 + 8)){
			Font* customFont = (Font*)(gameMemory + 8);
			char sizeX = customFont->charSize[*gameMemory] >> 4;
			sizeX = (sizeX + 1) % 9;
			customFont->charSize[*gameMemory] = (sizeX << 4) | (customFont->charSize[*gameMemory] & 0b00001111);
				*(gameMemory + 1) = true;
		}
		else if(!(mousePos.x < 8+1+8*9 || mousePos.x > 8+1+8*9 + 8 || mousePos.y < 8+1+3*9 || mousePos.y > 8+1+3*9 + 8)){
			Font* customFont = (Font*)(gameMemory + 8);
			char sizeX = customFont->charSize[*gameMemory] >> 4;
			sizeX = (sizeX + 8) % 9;
			customFont->charSize[*gameMemory] = (sizeX << 4) | (customFont->charSize[*gameMemory] & 0b00001111);
				*(gameMemory + 1) = true;
		}
		else if(!(mousePos.x < 8+1+8*9 || mousePos.x > 8+1+8*9 + 8 || mousePos.y < 8+1+5*9 || mousePos.y > 8+1+5*9 + 8)){
			Font* customFont = (Font*)(gameMemory + 8);
			char sizeY = customFont->charSize[*gameMemory] & 0b00001111;
			sizeY = (sizeY + 1) % 9;
			customFont->charSize[*gameMemory] = (customFont->charSize[*gameMemory] & 0b11110000) | sizeY;
				*(gameMemory + 1) = true;
		}
		else if(!(mousePos.x < 8+1+8*9 || mousePos.x > 8+1+8*9 + 8 || mousePos.y < 8+1+7*9 || mousePos.y > 8+1+7*9 + 8)){
			Font* customFont = (Font*)(gameMemory + 8);
			char sizeY = customFont->charSize[*gameMemory] & 0b00001111;
			sizeY = (sizeY + 8) % 9;
			customFont->charSize[*gameMemory] = (customFont->charSize[*gameMemory] & 0b11110000) | sizeY;
				*(gameMemory + 1) = true;
		}
		else if(!(mousePos.x < 4 || mousePos.x > GAME_WIDTH - 4 || mousePos.y < GAME_HEIGHT - (9*8) - 4 || mousePos.y > GAME_HEIGHT - 4)){
			char clickX = (mousePos.x - 4)/8;
			char clickY = (mousePos.y - (GAME_HEIGHT - (9*8) - 4))/8;

			*gameMemory = 29 * clickY + clickX;
		} 
		else if(!(mousePos.x < 8 + (8*9)+1 + 8 + 1 || mousePos.y < 8 + (6*9) || mousePos.x > 8 + (8*9)+1 + 8 + 1 + (5 * 8) - 2 || mousePos.y > 8 + (6*9)-1 + 18)){
			if(writeFile("resources/font.bin", gameMemory + 8, sizeof(Font))){
				//No unsaved changes
				*(gameMemory + 1) = false;
			}
		}
		else if(!(mousePos.x < 8 + (8*9)+1 + 8 + 1 || mousePos.y < 8 + (6*9) - 18 || mousePos.x > 8 + (8*9)+1 + 8 + 1 + (5 * 8) - 2 || mousePos.y > 8 + (6*9)-1 + 18 - 18)){
			Font* customFont = (Font*)(gameMemory + 8);
			memcpy(&font, customFont, sizeof(Font));
		}
	}
	return false;
}

bool ILIGAME::VM::tickDraw()
{
	ILIGAME::VM::clearScreen(0);

	for(int i = 0; i < 16; i++){
		ILIGAME::VM::drawRectRel(i*8, 0, 8, 8, i, true);
		ILIGAME::VM::drawText(std::to_string(i).c_str(), i*8 + (i < 10 ? 3 : 0), 1, i + 8 % 16);
	}
	
	ILIGAME::VM::drawRectRel(8, 8, 8*8 + 9, 8*8 + 9, 13, true);

	Font* customFont = (Font*)(gameMemory + 8);

	FontChar* currentChar = &customFont->charMasks[*gameMemory];
	for(int i = 0; i < 8; i++){
		for(int o = 0; o < 8; o++){
			if(o >= (customFont->charSize[*gameMemory] >> 4) || i >= (customFont->charSize[*gameMemory] & 0b00001111))
				ILIGAME::VM::drawRectRel(8 + 1 + o * 9, 8 + 1 + i * 9, 8, 8, 1, true);
			else
				ILIGAME::VM::drawRectRel(8 + 1 + o * 9, 8 + 1 + i * 9, 8, 8, ((currentChar->mask[i] & (0b10000000 >> o)) > 0? 0:7), true);
		}
	}
	
	ILIGAME::VM::drawText("x", 8+1+8*9 + 2, 8+1+0*9, 7);
	ILIGAME::VM::drawRectRel(8+1+8*9, 8+1+1*9, 8, 8, 8, true);
	ILIGAME::VM::drawText((char)208, 8+1+8*9, 8+1+1*9, 10);
	ILIGAME::VM::drawRectRel(8+1+8*9, 8+1+2*9-1, 8, 10, 7, true);
	ILIGAME::VM::drawText(('0' + (customFont->charSize[*gameMemory] >> 4)), 8+1+8*9 + 2, 8+1+2*9-1 + 2, 0);
	ILIGAME::VM::drawRectRel(8+1+8*9, 8+1+3*9, 8, 8, 8, true);
	ILIGAME::VM::drawText((char)209, 8+1+8*9, 8+1+3*9, 10);
	ILIGAME::VM::drawText("y", 8+1+8*9 + 2, 8+1+4*9, 7);
	ILIGAME::VM::drawRectRel(8+1+8*9, 8+1+5*9, 8, 8, 8, true);
	ILIGAME::VM::drawText((char)208, 8+1+8*9, 8+1+5*9, 10);
	ILIGAME::VM::drawRectRel(8+1+8*9, 8+1+6*9-1, 8, 10, 7, true);
	ILIGAME::VM::drawText('0' + (customFont->charSize[*gameMemory] & 0b00001111), 8+1+8*9 + 2, 8+1+6*9-1 + 2, 0);
	ILIGAME::VM::drawRectRel(8+1+8*9, 8+1+7*9, 8, 8, 8, true);
	ILIGAME::VM::drawText((char)209, 8+1+8*9, 8+1+7*9, 10);
	
	ILIGAME::VM::drawText(std::to_string(*gameMemory).c_str(), 8+1+9*9 + 2, 8+1+0*9 + 2, 7);

	ILIGAME::VM::drawRect(8 + (8*9)+1 + 8 + 1, 8 + (6*9) - 18, 8 + (8*9)+1 + 8 + 1 + (5 * 8) - 2, 8 + (6*9)-1 + 18 - 18, 8, true);
	ILIGAME::VM::drawText("APPLY", 8 + (8*9)+1 + 8 + 1 + 6, 8 + (6*9) + 6 - 18, 1);

	ILIGAME::VM::drawRect(8 + (8*9)+1 + 8 + 1, 8 + (6*9), 8 + (8*9)+1 + 8 + 1 + (5 * 8) - 2, 8 + (6*9)-1 + 18, *(gameMemory + 1) ? 8 : 5, true);
	ILIGAME::VM::drawText("SAVE", 8 + (8*9)+1 + 8 + 1 + 8, 8 + (6*9) + 6, 1);

	ILIGAME::VM::drawRect(0, GAME_HEIGHT - (9*8) - 8, GAME_WIDTH, GAME_HEIGHT, 14, true);
	for(int c = 0; c < 256; c++){
		FontChar* currentChar = &customFont->charMasks[c];
		for(int i = 0; i < 8; i++){
			for(int o = 0; o < 8; o++){
				ILIGAME::VM::drawPixel(4 + (c % 29) * 8 + o, GAME_HEIGHT - (9*8) - 4 + c / 29 * 8 + i, ((currentChar->mask[i] & (0b10000000 >> o)) > 0? 0:7));
			}
		}
	}
	ILIGAME::VM::drawText("Pretty Icons: \n\x01 - Font Editor \n\x02 - Map Editor \n\x03 - Tile Editor \n\x04 - Code Editor", 128 + 4, 3, 7);
	return false;
}

bool ILIGAME::VM::tickClose(){
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

	// Draw upto but not including x2
	x2 -= 1;

	for (int row = y1; row < y2; row++)
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
	drawRect(x, y, x + w, y + h, color, fill);
}

void ILIGAME::VM::drawText(const char text, unsigned char x, unsigned char y, unsigned char color)
{
	FontChar fontChar = font.charMasks[(unsigned char)text];
	for (int row = 0; row < (font.charSize[(unsigned char)text] & 0b00001111); row++)
	{
		unsigned char rowMask = fontChar.mask[row];
		unsigned char bitMask = 0b10000000;
		for (int col = 0; col < font.charSize[(unsigned char)text] >> 4; col++)
		{
			if (rowMask & (bitMask >> col))
			{
				drawPixel(x + col, y + row, color);
			}
		}
	}
}

void ILIGAME::VM::drawText(const char* text, unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char carriage = x;
	for (unsigned int i = 0; text[i] != '\0'; i++)
	{
		switch (text[i])
		{
		case '\n':
			y += (font.charSize[(unsigned char)text[i]] & 0b00001111) + 1;
			carriage = x;
			continue;
			break;
		case ' ':
			carriage += (font.charSize[(unsigned char)text[i]] >> 4) + 1;
			continue;
			break;
		}
		FontChar fontChar = font.charMasks[(unsigned char)text[i]];
		for (int row = 0; row < (font.charSize[(unsigned char)text[i]] & 0b00001111); row++)
		{
			unsigned char rowMask = fontChar.mask[row];
			unsigned char bitMask = 0b10000000;
			for (int col = 0; col < font.charSize[(unsigned char)text[i]] >> 4; col++)
			{
				if (rowMask & (bitMask >> col))
				{
					drawPixel(carriage + col, y + row, color);
				}
			}
		}
		carriage += (font.charSize[(unsigned char)text[i]] >> 4) + 1;
	}
}
