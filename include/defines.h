#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <FastLED.h>
#include <arduinoFFT.h>

#define CHANNEL A0 //3.47k
#define BUTTON1 D5 // ChangeMode
#define BUTTON2 D6 // ChangeColor
#define BUTTON3 D7 // ChangeBrightness
#define LED_PIN D8
#define NUM_LEDS 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NR_OF_MODS 5
#define NR_OF_COLORS 147

arduinoFFT FFT = arduinoFFT();
CRGB leds[NUM_LEDS];

const uint16_t samples = 256;           // This value MUST ALWAYS be a power of 2
const double samplingFrequency = 10000; // for 5000 Hz

const unsigned int sampling_period_us = round(1000000 * (1.0 / samplingFrequency));
const long interval = 200;
unsigned long prevoiusMillis = 0; // for debounce

int color = 0;     // change HUE
uint8_t value = 0; // to limit the values from the Fourier transform between 0-255
uint8_t currentMode = 0;
int currentStaticColor = 0;
int colorChanged = false;
int brightness = 50;
int rainbowSpeed = 20;

#endif