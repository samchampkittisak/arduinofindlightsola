#include "Arduino.h"
#include "LED.h"
 
LED led1 (13);
LED led2 (12);

void setup() {}
void loop() {
  led1.toggle();
  led1.on();
  led1.interval(500);
  led1.off(); 
  led1.interval(250);
  led2.toggle();
  led2.on();
  led2.interval(500);
  led2.off(); 
  led2.interval(250);
  }
