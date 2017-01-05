#define LED1 4 
#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8

#define THR A0
#define YAW A1
#define PIT A2
#define ROL A3
#define MOD A4
#define AUX A5


String data = "";

int chan[]={0,0,0,0,0,0};

void setup()  
{
  Serial.begin(57600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  
  pinMode(THR,OUTPUT);
  pinMode(YAW,OUTPUT);
  pinMode(PIT,OUTPUT);
  pinMode(ROL,OUTPUT);
  pinMode(MOD,OUTPUT);
  pinMode(AUX,OUTPUT);
}

void turn_off_leds(){
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
}

void loop()
{
  while(Serial.available()==0)
  {}

  char character;
  while(Serial.available()>0){
    character = Serial.read();
    //Serial.write(character);
  }

  if (character == '\n') {
    if (data.length() == 31) {
      if ( data[0] == '{' && data[30]=='}' ){
        
        for (int n = 0; n<6; n++){
          chan[n]=data.substring((4*n)+(n+1),(4*n)+(n+5)).toInt();
        }
        digitalWrite(THR,(chan[0]-1000)/4);
        digitalWrite(YAW,(chan[1]-1000)/4);
        digitalWrite(PIT,(chan[2]-1000)/4);
        digitalWrite(ROL,(chan[3]-1000)/4);
        digitalWrite(MOD,(chan[4]-1000)/4);
        digitalWrite(AUX,(chan[5]-1000)/4);
        /*
        Serial.print("(");
        Serial.print(chan[0]);
        Serial.print(",");
        Serial.print(chan[1]);
        Serial.print(",");
        Serial.print(chan[2]);
        Serial.print(",");
        Serial.print(chan[3]);
        Serial.print(",");
        Serial.print(chan[4]);
        Serial.print(",");
        Serial.print(chan[5]);
        Serial.println(")");
        */
        
      }
    }
    data = "";
  }else{
    data = data + character;
  }
}
