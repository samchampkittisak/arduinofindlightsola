#include "Arduino.h"
class Step
{
  public:
    Step(int n1, int n2, int n3, int n4);
    void stepper(int xw, boolean Direct);
    void SetDirection(boolean Direct);
  private:
    boolean Direction;
    int IN1;
    int IN2;
    int IN3;
    int IN4;
};
