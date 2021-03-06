#ifndef ILIGAME_H
#define ILIGAME_H

#define GAME_WIDTH 240
#define GAME_HEIGHT 160
#define FRAME_RATE 30

namespace ILIGAME
{
    struct Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    struct FontChar
    {
        unsigned char mask[8];
    };

    struct Font
    {
        unsigned char charSize[256]; // High nibble x, low nibble y
        FontChar charMasks[256];     // 1bpp 8x8 image data
    };

    struct Point
    {
    	unsigned char x;
    	unsigned char y;
    };

    enum MouseActions
    {
    	LEFT_CLICK = 1,
    	RIGHT_CLICK = 2,
    	MIDDLE_CLICK = 4,
    	WHEEL_UP = 8,
    	LEFT_CLICK_LAST = 16,
    	RIGHT_CLICK_LAST = 32,
    	MIDDLE_CLICK_LAST = 64,
		WHEEL_DOWN = 128,
    };

    class VM
    {
    protected:
        unsigned char gameScreen[GAME_HEIGHT][GAME_WIDTH];
        Color pallette[16] = {{0, 0, 0},
                              {29, 43, 83},
                              {126, 37, 83},
                              {0, 135, 81},
                              {171, 82, 54},
                              {95, 87, 79},
                              {194, 195, 199},
                              {255, 241, 232},
                              {255, 0, 77},
                              {255, 163, 0},
                              {255, 236, 39},
                              {0, 228, 54},
                              {41, 173, 255},
                              {131, 118, 156},
                              {255, 119, 168},
                              {255, 204, 170}};
        Font font;
		Point mousePos = {0,0};
		char mouseActions = 0;

        char* gameMemory;

    public:
        VM();
        virtual ~VM();

        virtual int run() = 0;
        virtual void flip();

		virtual unsigned int readFile(const char* filePath, char*& fileData) = 0;
		virtual bool writeFile(const char* filePath, void* fileData, unsigned int fileSize) = 0;

        void resetPallette();
        void resetFont();

		bool tickInit();
        bool tickUpdate();
        bool tickDraw();
        bool tickClose();

        void clearScreen(unsigned char color);
        void drawPixel(unsigned char x, unsigned char y, unsigned char color);
        void drawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color, bool fill);
        void drawRectRel(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color, bool fill);
        void drawText(const char text, unsigned char x, unsigned char y, unsigned char color);
        void drawText(const char *text, unsigned char x, unsigned char y, unsigned char color);
    };
}
#endif
