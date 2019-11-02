#include <Arduino.h>
#include "button.h"

#define PIN_BUTTON 5

Button button(PIN_BUTTON);

int delta = 20;
int difference = 120;
int *bluePins = new int[5] { 12, 11, 10, 9, 8 };
int *X = new int[5] { 255, 255 - difference, 255 - 2 * difference, 255 - 3 * difference, 255 - 4 * difference };
int *Y = new int[5] { 255, 255 - difference, 255 - 2 * difference, 255 - 3 * difference, 255 - 4 * difference };
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
        X[i] += delta;
        if (X[i] >= 0 && X[i] <= 255)
            Y[i] = X[i];
        else if (X[i] > 255 && X[i] <= 510)
            Y[i] = 510 - X[i];
        else
            Y[i] = 0;
        set_B(bluePins[i], Y[i]);
    }
    if (delta > 0 && X[ledsCount - 1] >= 255
      || delta < 0 && X[0] <= 255)
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
