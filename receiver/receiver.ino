//PWM Pins
#define THR 3
#define YAW 5
#define PIT 6
#define ROL 9
#define MOD 10
#define AUX 11

//For software serial
#define RX_PIN A2
#define TX_PIN A3

#include <SoftwareSerial.h>

SoftwareSerial rfSerial(RX_PIN , TX_PIN);

String data = "";
char character;
int chan[] = {0,0,0,0,0,0};
int signal = 0;

void setup()  
{
  rfSerial.begin(57600);
  Serial.begin(9600);
  
  pinMode(THR,OUTPUT);
  pinMode(YAW,OUTPUT);
  pinMode(PIT,OUTPUT);
  pinMode(ROL,OUTPUT);
  pinMode(MOD,OUTPUT);
  pinMode(AUX,OUTPUT);
}

void loop(){
  while(rfSerial.available()>0){
    character = rfSerial.read();
    if (character == ' ') {
      if (data.length() == 31) {
        if ( data[0] == '{' && data[30]=='}' ){
          ////////Serial.println(data);
          for (int n = 0; n<6; n++){
            chan[n]=data.substring((4*n)+(n+1),(4*n)+(n+5)).toInt();
          }
          Serial.print("(");
          analogWrite(THR,(chan[0]-1000)/4);
          Serial.print((chan[0]-1000)/4);
          Serial.print(",");
          analogWrite(YAW,(chan[1]-1000)/4);
          Serial.print((chan[1]-1000)/4);
          Serial.print(",");
          analogWrite(PIT,(chan[2]-1000)/4);
          Serial.print((chan[2]-1000)/4);
          Serial.print(",");
          analogWrite(ROL,(chan[3]-1000)/4);
          Serial.print((chan[3]-1000)/4);
          Serial.print(",");
          analogWrite(MOD,(chan[4]-1000)/4);
          Serial.print((chan[4]-1000)/4);
          Serial.print(",");
          analogWrite(AUX,(chan[5]-1000)/4);
          Serial.print((chan[5]-1000)/4);
          Serial.println(")");
          
          signal = 100;
        }
      }
      data = "";
    }else{
      data = data + character;
    }
  }
  if(rfSerial.available()<1){
    Serial.println(signal);
    if(signal < 5){
      Serial.print("(");
      analogWrite(THR,0);
      Serial.print(0);
      Serial.print(",");
      analogWrite(YAW,0);
      Serial.print(0);
      Serial.print(",");
      analogWrite(PIT,0);
      Serial.print(0);
      Serial.print(",");
      analogWrite(ROL,0);
      Serial.print(0);
      Serial.print(",");
      analogWrite(MOD,0);
      Serial.print(0);
      Serial.print(",");
      analogWrite(AUX,0);
      Serial.print(0);
      Serial.println(")");
    }
    signal -= 1;
  }
  
}
