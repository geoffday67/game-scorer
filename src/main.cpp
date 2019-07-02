#include <avr/power.h>
#include <avr/sleep.h>

#include "EventManager.h"
#include "Output.h"
#include "MainScreen.h"
#include "Players.h"

int keyPressed;
char buffer [32];

void KeypadHandler() {
  int a = digitalRead(3);
  int b = digitalRead(4);
  int c = digitalRead(5);
  int d = digitalRead(6);

  keyPressed = ((b*2)+a)*3 + (d*2) + c + 1;

  if (keyPressed == 0x0B) {
    keyPressed = KEY_0;
  }
}

void setup() {
  Output.begin();

  Players.restore();
  attachInterrupt(digitalPinToInterrupt(2), KeypadHandler, RISING);

  MainScreen.activate();
}

void loop() {
  power_all_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  power_all_enable();

  // A key press is the only thing that will wake us up
  EventManager.queueEvent(new KeyEvent(keyPressed));

  EventManager.processEvents();

  delay(100);
}