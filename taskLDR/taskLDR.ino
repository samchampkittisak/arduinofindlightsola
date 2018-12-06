#include <Arduino_FreeRTOS.h>
#include <SoftwareSerial.h>
#include "Step.h"

int meanmanual=150; //set mean light

unsigned long last_time;
unsigned long currentMillis ;
int steps_left=0;
long time;
Step stmotor(8, 9, 10, 11);
boolean Dire = true;

void TaskAnalogRead( void *pvParameters );
void TaskdatatoMCU(void *pvParameters);
void Taskstepmotor(void *pvParameters);
SoftwareSerial ArduinoSerial(3, 2); // RX | TX

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
    ,  (const portCHAR *) "stepmotor"
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
    // read the input on analog pin 0:
    int sensorValue0 = analogRead(A0);
    int sensorValue1 = analogRead(A1);
    int sensorValue2 = analogRead(A2);
    int sensorValue3 = analogRead(A3);
    float mean = (sensorValue0+sensorValue1+sensorValue2+sensorValue3)/4;
    // print out the value you read:
    Serial.print("A0(sensorUp) =");
    Serial.println(sensorValue0);
    Serial.print("A1(sensorDown) =");
    Serial.println(sensorValue1);
    Serial.print("A2(sensorLeft) =");
    Serial.println(sensorValue2);
    Serial.print("A3(sensorLight) =");
    Serial.println(sensorValue3);
    Serial.print("mean =");
    Serial.println(mean);
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
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
    while(steps_left>=0&&steps_left<4096){
    
    int LDR0 = analogRead(A0) ;
    int LDR1 = analogRead(A1) ;
    int LDR2 = analogRead(A2) ;
    int LDR3 = analogRead(A3) ;
    
    currentMillis = micros();
      if(currentMillis-last_time>=1000){
        if(LDR0>LDR1&&LDR0>LDR2&&LDR0>LDR3)
        {
          if(steps_left<2048){
            steps_left--;
            stmotor.stepper(1, false); 
            last_time=micros();
          }
            
          else{
            steps_left++;
            stmotor.stepper(1, true); 
            last_time=micros();
          } 
              
        }
        else if(LDR1>LDR0&&LDR1>LDR2&&LDR1>LDR3)
        {
          if(steps_left<2048){
            steps_left++;
            stmotor.stepper(1, true); 
            last_time=micros();
          }
          else{
            steps_left--;
            stmotor.stepper(1, false); 
            last_time=micros();
          }
        }
        else if(LDR2>LDR0&&LDR2>LDR1&&LDR2>LDR3)
        {
          if(steps_left<1024||steps_left>3072){
            steps_left++;
            stmotor.stepper(1, true); 
            last_time=micros();
          }
          else{
            steps_left--;
            stmotor.stepper(1, false); 
            last_time=micros();
          }    
        }
        else if(LDR3>LDR0&&LDR3>LDR1&&LDR3>LDR2)
        {
          if(steps_left<1024||steps_left>3072){
            --steps_left;
            stmotor.stepper(1, false); 
            last_time=micros();
          }
          else{
            steps_left++;
            stmotor.stepper(1, true); 
            last_time=micros();
          }    
        }
      }
    }
    if(steps_left<0)
      steps_left=4095;
    else if(steps_left>=4096)
      steps_left=0;
  }
}
