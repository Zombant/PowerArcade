#include <IRremote.h>

#define BUTTON_INPUT_PIN 6
#define TRANSISTOR_OUTPUT_PIN 9 //Green LED
#define IR_OUTPUT_PIN 3 //White LED

IRsend irsend;

bool isOn;

void setup() {
  Serial.begin(9600);

  isOn = true;

  pinMode(BUTTON_INPUT_PIN, INPUT);
  pinMode(TRANSISTOR_OUTPUT_PIN, OUTPUT);
  //IR OUTPUT PIN IS AUTOMATICALLY SET TO PWM PIN 3

  //Onboard LED pin
  pinMode(13, OUTPUT);
}

void loop() {
  Serial.println(isOn);
  if(digitalRead(BUTTON_INPUT_PIN) == 1 && !isOn){
    startupSequence();
    delay(240000);
  } else if(digitalRead(BUTTON_INPUT_PIN) == 1 && isOn) {
    shutdownSequence();
    delay(240000);
  }
}

void startupSequence(){
  Serial.println("STARTUP");
  isOn = true;

  //send IR signal
  irsend.sendNEC(0x40BE629D, 32);
  digitalWrite(13, HIGH);
  delay(10000);
  
  //send brief HIGH signal to transistor
  digitalWrite(13, HIGH);
  digitalWrite(TRANSISTOR_OUTPUT_PIN, HIGH);
  delay(50);
  digitalWrite(TRANSISTOR_OUTPUT_PIN, LOW);
  delay(3000);
  digitalWrite(13, LOW);
}



void shutdownSequence(){
  Serial.println("SHUTDOWN");
  isOn = false;
  
  //send IR signal
  irsend.sendNEC(0x40BE629D, 32);
  digitalWrite(13, HIGH);
  delay(10000);
  
  //send brief HIGH signal to transistor
  digitalWrite(13, HIGH);
  digitalWrite(TRANSISTOR_OUTPUT_PIN, HIGH);
  delay(50);
  digitalWrite(TRANSISTOR_OUTPUT_PIN, LOW);
  delay(3000);
  digitalWrite(13, LOW);
}
