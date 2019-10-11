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

//Led leds[5] = { Led(6, 7, 8), Led(9, 10, 11), Led(12, 13, 14), Led(15, 16, 17), Led(18, 19, 20) };
Led leds[5] = { Led(6, 7, 8), Led(9, 10, 11), Led(31, 33, 35), Led(37, 39, 41), Led(43, 45, 47) };
int currentLedNumber = 0;
bool waveOn = false;

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
    Led currentLed = leds[currentLedNumber];
    int nextLedNumber = (currentLedNumber + 1) % 5;
    Led nextLed = leds[nextLedNumber];
    for (int i = 255; i >= 0; i--)
    {
        if (checkOff())
            return;
        delay(20);
        set_rgb_led(currentLed, i, i, i);
        delay(20);
        set_rgb_led(nextLed, 255 - i, 255 - i, 255 - i);
    }

    currentLedNumber = nextLedNumber;
}

void offAllLeds()
{
    for (Led led: leds)
    {
        set_rgb_led(led);
    }
}
