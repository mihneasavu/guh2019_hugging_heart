#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Servo.h>


Servo leftServo;
Servo rightServo;

//define some pins
const int buttonPin = 2;
const int boardLED = 13;
const int leftServoPin = 9;
const int rightServoPin = 10;
float pressureSensorValue = 0;
const int pressureSensor = A3;
int totalTicks = 0;
int tickesOverThreshhold = 0;

bool hug = false;
int buttonState = 0;



void setup() {
  pinMode(13, OUTPUT);
  pinMode(pressureSensor, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  // connect to the servos
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  
  // reset them 
  rightServo.write(20);
  leftServo.write(110);
  delay(100);

}
void performHug() {

  rightServo.write(80);
  leftServo.write(40);

  delay (2000);

  rightServo.write(20);
  leftServo.write(110);
}

void loop() {

  pressureSensorValue = analogRead(pressureSensor);

  if (hug) {
    performHug();
    hug = false;
//    delay(1000);
//    Serial.println("hug in progress yay");
//    delay(1000);

  }

  // check if the button is pressed. If it is, the buttonState is HIGH:
  Serial.print(pressureSensorValue);
  Serial.print(" ");
  Serial.print(tickesOverThreshhold);
    Serial.print("/");
  Serial.print(totalTicks);
    Serial.print("\n");


  totalTicks++;
  if (pressureSensorValue < 21) {
    tickesOverThreshhold ++;
    if(totalTicks > 50) {tickesOverThreshhold = 0;  totalTicks = 0;}
    if(tickesOverThreshhold >= 0.8*totalTicks && (tickesOverThreshhold >10 && totalTicks > 10))
    {
          digitalWrite(13, HIGH);
          Serial.println("Hug");
          hug = true;
          tickesOverThreshhold = 0;
          totalTicks = 0;
    }
  } else {
    digitalWrite(13, LOW);
  }
}
