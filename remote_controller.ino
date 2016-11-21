#include <ArduinoJson.h>

#define THROTTLE A0
#define YAW A1
#define PITCH A2
#define ROLL A3
#define AUX1 A4
#define AUX2 A5
#define REF_RATE 200      //milliseconds
#define SW_L D2
#define SW_R D3
#define LED1 D4 
#define LED2 D5
#define LED3 D6
#define LED4 D7
#define LED5 D8


int thro = 0, yaw = 0, pitch = 0, roll = 0, aux1 = 0, aux2 = 0;

void setup() {
  Serial.begin(57600);
}

void loop() {
  //thro = analogRead(THROTTLE);
  //yaw = analogRead(YAW);
  //pitch = analogRead(PITCH);
  //roll = analogRead(ROLL);
  //aux1 = analogRead(AUX1);
  //aux2 = analogRead(AUX2);
  thro = analogRead(THROTTLE);
  yaw = analogRead(YAW);
  pitch = analogRead(PITCH);
  roll = analogRead(ROLL);
  aux1 = analogRead(AUX1);
  aux2 = analogRead(AUX2);

  Serial.print(String(thro+1000) + "-");
  Serial.print(String(yaw+1000) + "-");
  Serial.print(String(pitch+1000) + "-");
  Serial.print(String(roll+1000) + "-");
  Serial.print(String(aux1+1000) + "-");
  Serial.println(aux2+1000);
  
  delay(REF_RATE);
}
