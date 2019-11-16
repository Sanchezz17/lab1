#include <Arduino.h>
#include "button.h"

#define PIN_BUTTON 5

Button button(PIN_BUTTON);

int delta = 20;
const int difference = 120;
int bluePins[5] = { 12, 11, 10, 9, 8 };
int pinPosition[5] = { 255, 255 - difference, 255 - 2 * difference, 255 - 3 * difference, 255 - 4 * difference };
int blueBrightness[5] = { 255, 255 - difference, 255 - 2 * difference, 255 - 3 * difference, 255 - 4 * difference };
int ledsCount = 5;

bool waveOn = false;

void set_B(int pin, int B = 0)
{
    analogWrite(pin, 255 - B);
}

void setup()
{
    for (int i = 0; i < ledsCount; i++)
    {
        pinMode(bluePins[i], OUTPUT);
    }
    turnOffAllLeds();
}

void loop() 
{
    if (button.wasPressed())
    {
      toggle();
    }
    if (waveOn)
    {
        delay(40);
        waveIteration();  
    }
}

void toggle() {
    waveOn = !waveOn;
    if (!waveOn)
        turnOffAllLeds();
}

void waveIteration()
{
    for (int i = 0; i < ledsCount; i++)
    {
        pinPosition[i] += delta;
        if (pinPosition[i] >= 0 && pinPosition[i] <= 255)
            blueBrightness[i] = pinPosition[i];
        else if (pinPosition[i] > 255 && pinPosition[i] <= 510)
            blueBrightness[i] = 510 - pinPosition[i];
        else
            blueBrightness[i] = 0;
        set_B(bluePins[i], blueBrightness[i]);
    }
    if (delta > 0 && pinPosition[ledsCount - 1] >= 255
      || delta < 0 && pinPosition[0] <= 255)
    {
        delta = -delta;
    }
}

void turnOffAllLeds()
{
    for (int i = 0; i < ledsCount; i++)
    {
        set_B(bluePins[i]);
    }
}
