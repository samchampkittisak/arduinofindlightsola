#include "Arduino.h"
#include "LED.h"

LED::LED(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void LED::on() { digitalWrite(_pin, HIGH); }
void LED::off() { digitalWrite(_pin, LOW); }
void LED::interval(int p) { delay(p); }

void LED::toggle(int x)
{
  LED::on();  LED::interval(x);
  LED::off(); LED::interval(x);
}
