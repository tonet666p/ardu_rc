#include <ArduinoJson.h>

// Constants for adapt to other arduino boards
// Analog Inputs
#define THROTTLE A0
#define YAW A1
#define PITCH A2
#define ROLL A3
#define MODE A4
#define AUX A5
// Digital Inputs
#define SW_L 2
#define SW_R 3
// Digital Outputs
#define LED1 4 
#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8
// End of Constants
#define REF_RATE 100      //Refresh rate in milliseconds


int thr = 0, yaw = 0, pit = 0, rol = 0, mod = 0, aux = 1500;
int sw_l_status = 1, sw_r_status = 1;
int current_mode = 1;

StaticJsonBuffer<200> jsonBuffer;
JsonObject& json = jsonBuffer.createObject();

void turn_off_leds(){
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
}

void turn_on_led(int led){
  turn_off_leds();
  digitalWrite(led,HIGH);
}

void switch_mode(){
  if(sw_l_status == 0){
    switch(current_mode){
      case 1:
        set_mode(5);
        break;
      case 2:
        set_mode(1);
        break;
      case 3:
        set_mode(2);
        break;
      case 4:
        set_mode(3);
        break;
      case 5:
        set_mode(4);
        break;
      default:
        break;
    }
  }
  if(sw_r_status == 0){
    switch(current_mode){
      case 1:
        set_mode(2);
        break;
      case 2:
        set_mode(3);
        break;
      case 3:
        set_mode(4);
        break;
      case 4:
        set_mode(5);
        break;
      case 5:
        set_mode(1);
        break;
      default:
        break;
    }
  }
}

void set_mode(int m){
  switch(m){
    case 1:
      turn_on_led(LED1);
      current_mode = 1;
      mod = 1000;      // 0 - 1230
      break;
    case 2:
      turn_on_led(LED2);
      current_mode = 2;
      mod = 1290;      // 1231 - 1360
      break;
    case 3:
      turn_on_led(LED3);
      current_mode = 3;
      mod = 1410;      // 1361 - 1490
      break;
    case 4:
      turn_on_led(LED4);
      current_mode = 4;
      mod = 1560;      // 1491 - 1620
      break;
    case 5:
      turn_on_led(LED5);
      current_mode = 5;
      mod = 1690;      // 1621 - 1749
      break;
    default:
      break;
  }
}

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(SW_L,INPUT_PULLUP);
  pinMode(SW_R,INPUT_PULLUP);
  set_mode(current_mode);
  Serial.begin(57600);
}

void loop() {
  /*
  Norlmally RC controllers returns values between 1000 and 2000, that explains
  why we are using +1000 to the next variables, because potentiometers returns values
  between 0 and 1000.
  */
  thr = analogRead(THROTTLE) + 1000;
  yaw = analogRead(YAW) + 1000;
  pit = analogRead(PITCH) + 1000;
  rol = analogRead(ROLL) + 1000;
  
  json["thr"]=thr;
  json["yaw"]=yaw;
  json["pit"]=pit;
  json["rol"]=rol;
  json["mod"]=mod;
  json["aux"]=aux;
  
  // Send JSON data using a RF module like HC-06, HC-05, HC-12, etc
  // Example: {"thr":1510,"yaw":1504,"pit":1502,"rol":1516,"mod":1000,"aux":1500}
  json.printTo(Serial);
  Serial.println();
  
  sw_l_status = digitalRead(SW_L);
  sw_r_status = digitalRead(SW_R);
  
  if(sw_l_status == 0 || sw_r_status == 0){
    switch_mode();
    delay(100);      //cause we (human beens) are slow pressing buttons :)
  }
  
  delay(REF_RATE);
}
