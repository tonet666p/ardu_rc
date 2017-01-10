# Arduino Remote Controller
This is a simple code for make a remote controller with two arduinos, it can be usable for control things like quadcopters, robers or everything you want to build and control remotely, it has 6 channels (THROTTLE, YAW, PITCH, ROLL, MODE, AUXILIAR), if you want you can add more channels with some code modifications but share your code if you do that and help to our community.

The code is did for Arduino Nano but you can use other Arduino board changing parameters at the begining of two code files, you need to modify the following lines:
## remote_controller.ino
```c++
// Analog Inputs (Connected to Joysticks)
#define THROTTLE A0
#define YAW A1
#define PITCH A2
#define ROLL A3
#define MODE A4
#define AUX A5

// Digital Inputs (Joystick builtin switchs for change modes)
#define SW_L 2
#define SW_R 3

// Digital Outputs (Only for show the current flight mode, currently are supported 5 flight modes)
#define LED1 4 
#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8

// This is the refresh rate in milliseconds
#define REF_RATE 25 
```
## receiver.ino
```c++
//receiver.ino
// PWM Outputs (keep in mind, that pins need to has PWM support)
#define THR 3
#define YAW 5
#define PIT 6
#define ROL 9
#define MOD 10
#define AUX 11

//For software serial (Connected to your RF module, I'm using HC-12 for send data wirelessly)
#define RX_PIN A2
#define TX_PIN A3
```

# Disclaimer
I clean my hands like Pontius Pilate :) , this work is still not tested and it can had some bugs, you can break your drone, kill your cat or begin the zombie apocalipse (I always wanted to say it!!). Happy making.
