#ifndef _HELPERS_H_
#define _HELPERS_H_

ICACHE_RAM_ATTR void changeMode()
{
    unsigned long currentMillis = millis();

    if (!digitalRead(BUTTON1) && currentMillis - prevoiusMillis > interval)
    {
        prevoiusMillis = currentMillis;

        currentMode++;
        if (currentMode > NR_OF_MODS)
        {
            currentMode = 0;
        }
        if (!colorChanged)
        {
            colorChanged = true;
        }
    }
}

ICACHE_RAM_ATTR void changeColor()
{
    unsigned long currentMillis = millis();

    if (!digitalRead(BUTTON2) && currentMillis - prevoiusMillis > interval)
    {
        prevoiusMillis = currentMillis;
        if (currentMode == 5)
        {
            rainbowSpeed -= 2;
            if (rainbowSpeed < 0)
            {
                rainbowSpeed = 20;
            }
        }
        else
        {
            currentStaticColor++;

            if (currentStaticColor > NR_OF_COLORS)
            {
                currentStaticColor = 0;
            }
            colorChanged = true;
        }
    }
}

ICACHE_RAM_ATTR void changeBrightness()
{
    unsigned long currentMillis = millis();

    if (!digitalRead(BUTTON3) && currentMillis - prevoiusMillis > interval)
    {
        prevoiusMillis = currentMillis;

        brightness += 25;

        if (brightness > 250)
        {
            brightness = 50;
        }
        colorChanged = true;
    }
}

void sleep(int timeToSleep, int currentmode)
{
    unsigned long start = millis();
    while (millis() - start < timeToSleep)
    {
        if (currentmode != currentMode)
        {
            return;
        }
    }
    ESP.wdtFeed(); // reset the WatchDog Timer
}

#endif
