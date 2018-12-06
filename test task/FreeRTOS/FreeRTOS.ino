#include <Arduino_FreeRTOS.h>
#include <SoftwareSerial.h>
#include "Step.h"

unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;
Step stmotor(8, 9, 10, 11);
boolean Dire = true;

void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

SoftwareSerial ArduinoSerial(3, 2);
void setup() {
  ArduinoSerial.begin(4800);

  Serial.begin(9600);
  
  while (!Serial) {
    ; 
  }
    
  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    TaskdatatoMCU
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1 // Priority
    ,  NULL );

  xTaskCreate(
    Taskstepmotor
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1 // Priority
    ,  NULL );
}

void loop()
{

}


void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    int sensorValue0 = analogRead(A0);
    int sensorValue1 = analogRead(A1);
    int sensorValue2 = analogRead(A2);
    int sensorValue3 = analogRead(A3);
    // print out the value you read:
    Serial.print("A0(sensorUp) =");
    Serial.println(sensorValue0);
    Serial.print("A1(sensorDown) =");
    Serial.println(sensorValue1);
    Serial.print("A2(sensorLeft) =");
    Serial.println(sensorValue2);
    Serial.print("A3(sensorLight) =");
    Serial.println(sensorValue3);
    
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskdatatoMCU(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
     float val = ArduinoSerial.parseFloat();
     if (val == 0xA0) {
        int Analog0 = analogRead(A0);
        int Analog1 = analogRead(A1);
        int Analog2 = analogRead(A2);
        int Analog3 = analogRead(A3);
        ArduinoSerial.print("LDRup = ");
        ArduinoSerial.println(Analog0); 
        ArduinoSerial.print("LDRdown = ");
        ArduinoSerial.println(Analog1);
        ArduinoSerial.print("LDRleft = ");
        ArduinoSerial.println(Analog2);
        ArduinoSerial.print("LDRlight = ");  
        ArduinoSerial.println(Analog3);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
}

void Taskstepmotor(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    
  }
}
