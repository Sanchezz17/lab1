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

int ledsCount = 5;
int difference = 80;
int *X = new int[5] { 255, 255 - difference, 255 - 2 * difference, 255 - 3 * difference, 255 - 4 * difference };
int *Y = new int[5] { 255, 255 - difference, 255 - 2 * difference, 255 - 3 * difference, 255 - 4 * difference };
Led *leds = new Led[5] { 
  Led(9, 10, 11),
  Led(6, 7, 8),
  Led(4, 3, 2),
  Led(37, 39, 41),
  Led(36, 38, 40) 
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
    for (int i = 0; i < ledsCount; i++)
    {
        Led led = leds[i];
        pinMode(led.GetR_OUT(), OUTPUT);
        pinMode(led.GetG_OUT(), OUTPUT);
        pinMode(led.GetB_OUT(), OUTPUT);
    }
    turnOffAllLeds();
    Serial.begin(115200);
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
        Led led = leds[i];
        Serial.println(X[i]);
        X[i] += delta;
        Serial.println(X[i]);
        if (X[i] >= 0 && X[i] <= 255)
            Y[i] = X[i];
        else if (X[i] > 255 && X[i] <= 510)
            Y[i] = 510 - X[i];
        else
            Y[i] = 0;
        set_rgb_led(led, Y[i], Y[i], Y[i]);
        /*Serial.print(led.X);
        Serial.print(" ");
        Serial.println(led.Y);*/
    }
    Serial.println();
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
        set_rgb_led(leds[i]);
    }
}
