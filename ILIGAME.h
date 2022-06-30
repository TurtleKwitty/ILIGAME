#define GAME_WIDTH 240
#define GAME_HEIGHT 160
#define FRAME_RATE 30

namespace ILIGAME
{
    struct Color
    {
        char r;
        char g;
        char b;
    };

    class VM
    {
        char gameScreen[GAME_HEIGHT][GAME_WIDTH];
        // TODO: Use pallette that is not pico-8 by default
        Color pallette[16]{{0, 0, 0}, {29, 43, 83}, {126, 37, 83}, {0, 135, 81}, {171, 82, 54}, {95, 87, 79}, {194, 195, 199}, {255, 241, 232}, {255, 0, 77}, {255, 163, 0}, {255, 236, 39}, {0, 228, 54}, {41, 173, 255}, {131, 118, 156}, {255, 119, 168}, {255, 204, 170}};

        VM();

    public:
        void clearScreen(char color);
        void drawRect(char x1, char y1, char x2, char y2, char color, bool fill = false);
        void drawRectRel(char x, char y, char w, char h, char color, bool fill = false);
        virtual void flip();
    };
}