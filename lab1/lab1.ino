#include <Arduino.h>
#include "button.h"
using namespace std;

#define PIN_BUTTON 5

Button button(PIN_BUTTON);

class Led 
{
public:
    Led(int r_out, int g_out, int b_out, int initialXY)
    {
        R_OUT = r_out;
        G_OUT = g_out;
        B_OUT = b_out;
        X = Y = initialXY;
    }
    int X;
    int Y;
    
    int GetR_OUT() { return R_OUT; }
    int GetG_OUT() { return G_OUT; }
    int GetB_OUT() { return B_OUT; }
private:
    int R_OUT;
    int G_OUT;
    int B_OUT;
};

int ledsCount = 5;
int difference = 60;
Led leds[5] = { 
  Led(9, 10, 11, 255),
  Led(6, 7, 8, 255 - difference),
  Led(31, 33, 35, 255 - 2 * difference),
  Led(37, 39, 41, 255 - 3 * difference),
  Led(43, 45, 47, 255 - 4 * difference) 
};
bool waveOn = false;
int delta = 5;

void set_rgb_led(Led led, int R = 0, int G = 0, int B = 0)
{
    analogWrite(led.GetR_OUT(), 255 - R);
    analogWrite(led.GetG_OUT(), 255 - G);
    analogWrite(led.GetB_OUT(), 255 - B);
}

void setup()
{
    for (Led led: leds)
    {
        pinMode(led.GetR_OUT(), OUTPUT);
        pinMode(led.GetG_OUT(), OUTPUT);
        pinMode(led.GetB_OUT(), OUTPUT);
    }
    offAllLeds();
}

void loop() 
{
    checkOff();
    if (waveOn)
    {
        delay(20);
        waveIteration();  
    }
}

bool checkOff() {
    if (button.wasPressed())
    {
        waveOn = !waveOn;
        if (!waveOn)
        {
            offAllLeds();
            return true;
        }
    }
    return false;
}

void waveIteration()
{
    for (Led led: leds)
    {
        led.X += delta;
        if (led.X >= 0 && led.X <= 255)
            led.Y = led.X;
        else if (led.X > 255 && led.X <= 510)
            led.Y = 510 - led.X;
        else
            led.X = 0;
        set_rgb_led(led, led.Y, led.Y, led.Y);
    }
    if (delta > 0 && leds[ledsCount - 1].X >= 255
      || delta < 0 && leds[0].X <= 255)
    {
        delta = -delta;
    }
}

void offAllLeds()
{
    for (Led led: leds)
    {
        set_rgb_led(led);
    }
}
