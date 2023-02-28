#ifndef _STYLE_H_
#define _STYLE_H_

#include "colors.h"
#include "helpers.h"

byte *Wheel(byte WheelPosition) {
  static byte c[3];
 
  if(WheelPosition < 85) {
   c[0] = WheelPosition * 3;
   c[1] = 255 - WheelPosition * 3;
   c[2] = 0;
  }
  else if(WheelPosition < 170) {
   WheelPosition -= 85;
   c[0] = 255 - WheelPosition * 3;
   c[1] = 0;
   c[2] = WheelPosition * 3;
  }
  else {
   WheelPosition -= 170;
   c[0] = 0;
   c[1] = WheelPosition * 3;
   c[2] = 255 - WheelPosition * 3;
  }

  return c;
}

void rainbowCycle(int rainbowSpeed) {
  byte *c;
  uint16_t i, j;

  for(j=0; j < 256; j++) {
    for(i=0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      leds[NUM_LEDS - 1 - i].setRGB(*c, *(c+1), *(c+2));
    }
    FastLED.show();
    sleep(rainbowSpeed, 5);
  }
}

void fadeColor()
{
    int color = colour[random(148)];
    fill_solid(leds, NUM_LEDS, color);

    for (int i = 0; i < brightness; i++)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        sleep(25, 3);
    }

    sleep(1000, 3);

    for (int i = brightness; i > 0; i--)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        sleep(25, 3);
    }
}

void staticColor()
{
    if (colorChanged)
    {
        for (int j = 0; j < NUM_LEDS; j++)
        {
            leds[j] = colour[currentStaticColor];
        }
        // to be changed.
        FastLED.setBrightness(brightness);
        FastLED.show();
        colorChanged = false;
    }
}

void pong()
{
    byte variant = random(148);
    FastLED.setBrightness(brightness);
    unsigned long currentColor = colour[variant]; // colour[random(148)];
    for (int i = 1; i < NUM_LEDS; i++)
    {
        leds[i] = currentColor;
        leds[i - 1] = currentColor;
        FastLED.show();
        sleep(75, 1);
        leds[i] = 0x000000;
        leds[i - 1] = 0x000000;
    }

    variant = random(148);
    currentColor = colour[variant];
    for (int i = NUM_LEDS; i > 0; i--)
    {
        leds[i] = currentColor;
        leds[i - 1] = currentColor;
        FastLED.show();
        sleep(75, 1);
        leds[i] = 0x000000;
        leds[i - 1] = 0x000000;
    }
}

void fire()
{
    int a = millis();
    for (int i = NUM_LEDS / 2; i < NUM_LEDS; i++)
    {
        uint8_t noise = inoise8(0, i * 60 + a, a / 2);
        uint8_t math = abs8(i - (NUM_LEDS / 2)) * 255 / (NUM_LEDS / 2);
        uint8_t index = qsub8(noise, math);
        leds[i] = ColorFromPalette(firePalette, index, 150);
    }

    for (int i = NUM_LEDS / 2 - 1; i >= 0; i--)
    {
        uint8_t noise = inoise8(0, i * 60 + a, a / 2);
        uint8_t math = abs8(i - (NUM_LEDS / 2 - 1)) * 255 / (NUM_LEDS / 2);
        uint8_t index = qsub8(noise, math);
        leds[i] = ColorFromPalette(firePalette, index, 150);
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
    sleep(100, 4);
}

void getAmps(double *vData, uint16_t bufferSize)
{
    double frec = 0.0;
    double frecs[6] = {};
    double amps[6] = {};
    for (uint16_t i = 5; i < bufferSize; i++)
    {
        frec = ((i * 1.0 * samplingFrequency) / samples);
        if (frec > 195 && frec < 550)
        {
            if (vData[i] > amps[0])
            {
                frecs[0] = frec;
                amps[0] = vData[i];
            }
        }
        else if (frec > 551 && frec < 1000)
        {
            if (vData[i] > amps[1])
            {
                frecs[1] = frec;
                amps[1] = vData[i];
            }
        }
        else if (frec > 1001 && frec < 1500)
        {
            if (vData[i] > amps[2])
            {
                frecs[2] = frec;
                amps[2] = vData[i];
            }
        }
        else if (frec > 1501 && frec < 2000)
        {
            if (vData[i] > amps[3])
            {
                frecs[3] = frec;
                amps[3] = vData[i];
            }
        }
        else if (frec > 2001 && frec < 3000)
        {
            if (vData[i] > amps[4])
            {
                frecs[4] = frec;
                amps[4] = vData[i];
            }
        }
        else if (frec > 3001 && frec < 4000)
        {
            if (vData[i] > amps[5])
            {
                frecs[5] = frec;
                amps[5] = vData[i];
            }
        }
    }
    color = 0;
    value = 0;
    for (int i = 0; i < 6; i++)
    {
        // hangolni!!!
        if (amps[i] < 8500)
        {
            value = 50;
        }
        else
        {
            value = map(amps[i], 8500, 38000, 70, 200);
        }
        leds[i * 2] = CHSV(color, 255, value);
        leds[(i * 2) + 1] = CHSV(color, 255, value);
        color += 255 / NUM_LEDS;
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
}

void musicVisualizer()
{
    static double vReal[samples];
    static double vImag[samples];
    /*SAMPLING*/
    static unsigned long microseconds = micros();
    for (int i = 0; i < samples; i++)
    {
        vReal[i] = analogRead(CHANNEL);
        vImag[i] = 0;
        while (micros() - microseconds < sampling_period_us)
        {
            // empty loop
        }
        microseconds += sampling_period_us;
    }
    FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
    FFT.Compute(vReal, vImag, samples, FFT_FORWARD);                 /* Compute FFT */
    FFT.ComplexToMagnitude(vReal, vImag, samples);                   /* Compute magnitudes */

    getAmps(vReal, (samples >> 1));
}

#endif // _STYLES_H_