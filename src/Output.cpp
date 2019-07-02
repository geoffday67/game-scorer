#include "Output.h"

#define TFT_DC 9
#define TFT_CS 10
#define BUFFPIXEL 80

classOutput Output;

classOutput::classOutput() {}

classOutput::~classOutput() {}

void classOutput::begin() {
  pTFT = new Adafruit_ILI9341(TFT_CS, TFT_DC);
  pTFT->begin();
  pTFT->setRotation(3);
  pTFT->setTextSize(2);

  // Get the width and height of a character in the current font
  int16_t x, y;
  uint16_t w, h;
  pTFT->getTextBounds("M", 0, 0, &x, &y, &w, &h);
  charWidth = w;
  charHeight = h;
  titleHeight = charHeight * 1.5;

  clear();
}

void classOutput::clear() {
  pTFT->fillScreen((uint16_t) Colours::Black);    
}

void classOutput::showTextAbsolute(int x, int y, const char *ptext, uint16_t foreground) {
  pTFT->setTextColor(foreground, COLOUR_BLACK);
  pTFT->setCursor(x, y);
  pTFT->print(ptext);
}

void classOutput::showText(int x, int y, const char *ptext, uint16_t foreground) {
  int absX = x * charWidth;
  int absY = titleHeight + (y * charHeight) + (charHeight / 2);
  showTextAbsolute(absX, absY, ptext, foreground);
}

void classOutput::showText_P(int x, int y, const char *ptext_P, uint16_t foreground) {
  char *pbuffer = new char [strlen_P(ptext_P) + 1];
  strcpy_P(pbuffer, ptext_P);
  showText(x, y, pbuffer, foreground);
  delete [] pbuffer;
}

void classOutput::showText(int x, int y, int n, uint16_t foreground) {
  char s [8];
  itoa (n, s, 10);
  showText(x, y, s, foreground);
}

void classOutput::showChar(int x, int y, char c, uint16_t foreground) {
  int absX = x * charWidth;
  int absY = titleHeight + (y * charHeight) + (charHeight / 2);
  pTFT->drawChar(absX, absY, c, foreground, COLOUR_BLACK, 2);
}

void classOutput::showTitle (const char *ptext) {
  int16_t x, y;
  uint16_t w, h;

  pTFT->fillRect(0, 0, SCREEN_WIDTH, titleHeight, COLOUR_PRIMARY);
  pTFT->getTextBounds(ptext, 0, 0, &x, &y, &w, &h);
  pTFT->setTextColor(COLOUR_WHITE, COLOUR_PRIMARY);
  pTFT->setCursor((pTFT->width() - w) / 2, charHeight / 4);
  pTFT->print(ptext);
}

void classOutput::showTitle_P (const char *ptext_P) {
  char *pbuffer = new char [strlen_P(ptext_P) + 1];
  strcpy_P(pbuffer, ptext_P);
  showTitle(pbuffer);
  delete [] pbuffer;
}

void classOutput::showFooter(const char *pleft, const char *pright) {
  int16_t x, y;
  uint16_t w, h;

  pTFT->getTextBounds(pright, 0, 0, &x, &y, &w, &h);
  pTFT->fillRect(0, SCREEN_HEIGHT - titleHeight, SCREEN_WIDTH, titleHeight, COLOUR_PRIMARY);
  pTFT->setTextColor(COLOUR_WHITE, COLOUR_PRIMARY);
  pTFT->setCursor(charWidth / 2, SCREEN_HEIGHT - titleHeight + charHeight / 4);
  pTFT->print(pleft);
  pTFT->setCursor(SCREEN_WIDTH - w - charWidth / 2, SCREEN_HEIGHT - titleHeight + charHeight / 4);
  pTFT->print(pright);
}

void classOutput::showFooter_P(const char *pleft_P, const char *pright_P) {
  char *plbuffer = new char [strlen_P(pleft_P) + 1]; strcpy_P(plbuffer, pleft_P);
  char *prbuffer = new char [strlen_P(pright_P) + 1]; strcpy_P(prbuffer, pright_P);
  showFooter(plbuffer, prbuffer);
  delete [] plbuffer; delete [] prbuffer;
}

void classOutput::showFooter(const char *pleft) {
  showFooter(pleft, "");
}

void classOutput::showFooter_P(const char *pleft_P) {
  char *plbuffer = new char [strlen_P(pleft_P) + 1]; strcpy_P(plbuffer, pleft_P);
  showFooter(plbuffer);
  delete [] plbuffer;
}

void classOutput::drawRectangle(int x, int y, int width, int height, Colours colour) {
  pTFT->drawRect(x, y, width, height, (int) colour);
}

void classOutput::fillRectangle(int x, int y, int width, int height, Colours colour) {
  pTFT->fillRect(x, y, width, height, (int) colour);
}

void classOutput::drawHorzLine(int x, int y, int length, Colours colour) {
  pTFT->drawFastHLine(x, y, length, (int) colour);
}

void classOutput::drawVertLine(int x, int y, int length, Colours colour) {
  pTFT->drawFastVLine(x, y, length, (int) colour);
}
