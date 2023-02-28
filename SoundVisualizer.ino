#include "include/defines.h"
#include "include/styles.h"

void setup()
{
  pinMode(CHANNEL, INPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON1), changeMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON2), changeColor, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON3), changeBrightness, FALLING);

  Serial.begin(115200);
  while (!Serial)
  {
  }
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear(); // clear all pixel data
}

void loop()
{
  vizualizer();
  ESP.wdtFeed(); // reset the WatchDog Timer
}

// to switch between modes.
void vizualizer()
{
  switch (currentMode)
  {
  case 0:
    FastLED.clear();
    musicVisualizer();
    break;
  case 1:
    FastLED.clear();
    pong();
    break;
  case 2:
    FastLED.clear();
    staticColor();
    break;
  case 3:
    FastLED.clear();
    fadeColor();
    break;
  case 4:
    FastLED.clear();
    fire();
    break;
  case 5:
    FastLED.clear();
    rainbowCycle(rainbowSpeed);
    break;
  default:
    break;
  }
}
