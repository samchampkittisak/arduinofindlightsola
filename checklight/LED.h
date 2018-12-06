#ifndef LED_h
#define LED_h
/***************************************************/
#include "Arduino.h"
class LED
{
  public:
    LED(int pin,int pin1,int pin2,int pin3,int pin4,int pin5,int pin6);
    void on();
    void off();
    void on1();
    void off1();
    void on2();
    void off2();
    void on3();
    void off3();
    void on4();
    void off4();
    void on5();
    void off5();
    void on6();
    void off6();
    void toggle(int x);
    void interval(int p);
    void Zero ();
    void One ();
    void Two();
    void Three();
    void Four();
    void Five();
    void Six();
    void Seven();
    void Eight();
    void Nine();
    void OFF();
    volatile byte state = 1 ;
    volatile byte statee = 1 ;
    void setNumber(int num);
    
  private:
    int _pin;
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int _pin5;
    int _pin6;
    
};
/***************************************************/
#endif

