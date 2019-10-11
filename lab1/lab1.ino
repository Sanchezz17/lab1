#include <Arduino.h>
#include "button.h"
using namespace std;

#define PIN_BUTTON 5

Button button(PIN_BUTTON);

class Led 
{
public:
    Led(int r_out, int g_out, int b_out)
    {
        R_OUT = r_out;
        G_OUT = g_out;
        B_OUT = b_out;
    }
    int GetR_OUT() { return R_OUT; }
    int GetG_OUT() { return G_OUT; }
    int GetB_OUT() { return B_OUT; }
private:
    int R_OUT;
    int G_OUT;
    int B_OUT;
};

Led leds[5] = { Led(6, 7, 8), Led(9, 10, 11), Led(12, 13, 14), Led(15, 16, 17), Led(18, 19, 20) };
int currentLedNumber = 0;
bool waveOn = false;

void set_rgb_led(Led led, int R = 255, int G = 255, int B = 255)
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
}

void loop() 
{
    if (button.wasPressed())
    {
        waveOn = !waveOn;
        if (!waveOn)
        {
            stopWave();
        }
    }
    if (waveOn)
    {
        waveIteration();  
    }
}

void waveIteration()
{
    set_rgb_led(leds[currentLedNumber], 0, 255, 0);
    delay(500);
    set_rgb_led(leds[currentLedNumber]);
    currentLedNumber = (currentLedNumber + 1) % 5;
}

void stopWave()
{
    for (Led led: leds)
    {
        set_rgb_led(leds[currentLedNumber]);
    }
}
