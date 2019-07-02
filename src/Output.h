#ifndef __OUTPUT__
#define __OUTPUT__

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <time.h>

/*
Display on a grid of 56 pixel units, this makes a nice button size.
=> 5 units across with left and right margin of 20 pixels,
and 4 units vertically with top and bottom margins of 8 pixels.
*/

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#define TOP_MARGIN      32//8
#define BOTTOM_MARGIN   8
#define LEFT_MARGIN     8
#define RIGHT_MARGIN    8
#define GRID_WIDTH      56
#define GRID_HEIGHT     56
#define LEFT_BUTTON_X   4
#define LEFT_BUTTON_Y   4//180
#define CENTRE_BUTTON_X (SCREEN_WIDTH - GRID_WIDTH) / 2
#define CENTRE_BUTTON_Y 4//180
#define RIGHT_BUTTON_X  260
#define RIGHT_BUTTON_Y  4//180
#define SCREEN_CENTRE   -1

#define COLOUR_PRIMARY  0xFAA4
#define COLOUR_LIGHT_PRIMARY  0xFE77
#define COLOUR_ACCENT   0x4D6A
#define COLOUR_TEXT     0xFFFF
#define COLOUR_WHITE    0xFFFF
#define COLOUR_BLACK    0x0000

enum class Colours: uint16_t {
    Black = 0x0000,
    White = 0xFFFF,
    LightGrey = 0xC618,
    DarkGrey = 0x7BEF,
    Orange = 0xFDA0,
    Red = 0xF800,
    Green = 0x07E0,
    Blue = 0x001F,
    Navy = 0x000F,
    DarkGreen = 0x03E0,
    DarkCyan = 0x03EF,
    Maroon = 0x7800,
    Purple = 0x780F,
    Olive = 0x7BE0,
    Cyan = 0x07FF,
    Magenta = 0x781F,
    Yellow = 0xFFE0,
    GreenYellow = 0xB7E0,
    Pink = 0xFC9F,
    Primary = 0x5722,
    Accent = 0xAF50,
    Text = 0x2121
};

class classOutput {
public:
    classOutput();
    virtual ~classOutput();
    virtual void begin();
    virtual void clear();
    virtual void showTextAbsolute(int x, int y, const char *ptext, uint16_t foreground);
    virtual void showText(int x, int y, const char *ptext, uint16_t foreground);
    virtual void showText_P(int x, int y, const char *ptext_P, uint16_t foreground);
    virtual void showText(int x, int y, int n, uint16_t foreground);
    virtual void showChar(int x, int y, char c, uint16_t foreground);
    virtual void showTitle(const char *ptext);
    virtual void showTitle_P(const char *ptext_P);
    virtual void showFooter(const char *pleft, const char *pright);
    virtual void showFooter_P(const char *pleft_P, const char *pright_P);
    virtual void showFooter(const char *pleft);
    virtual void showFooter_P(const char *pleft_P);
    virtual void drawRectangle(int x, int y, int width, int height, Colours colour);
    virtual void fillRectangle(int x, int y, int width, int height, Colours colour);
    virtual void drawHorzLine(int x, int y, int length, Colours colour);
    virtual void drawVertLine(int x, int y, int length, Colours colour);

private:
    Adafruit_ILI9341* pTFT;
    unsigned charWidth, charHeight, titleHeight;
};

extern classOutput Output;

#endif
