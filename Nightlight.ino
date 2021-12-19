#include <IRremote.h>

int motorPin1 = 3; // motor pin, it's analog
int motorPin2 = 11; // motor pin, it's analog

unsigned long onButton = 0xA32AB931;
unsigned long testButton = 0x2C2E80FF;

boolean on = false;

int wait = 500;
int fast = 500;

int RECEIVE_PIN = 7; //digital
IRrecv irreceiver(RECEIVE_PIN);
decode_results results;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  Serial.begin(9600);
  irreceiver.enableIRIn(); // Start the receiver
}

void loop() {
  if (irreceiver.decode(&results)) {
    if (results.value == onButton || results.value == testButton) {
      Serial.println("Power button pressed");
      if (on) {
        on = false;
      } else {
        on = true;
      }
    }
    
    Serial.println(results.value, HEX);
    delay(150);
    irreceiver.resume(); 
  }

  if (on) {
    //Sends the bubble ring down into solution
    digitalWrite(motorPin1, HIGH);
    //analogWrite(motorPin1, 255);
    analogWrite(motorPin2, 0);
    delay(fast);
    analogWrite(motorPin1, 0);
    delay(wait);
    
    //Bring bubble ring back up
    analogWrite(motorPin2, 255);
    delay(fast);
    analogWrite(motorPin2, 0);
    delay(wait);
    
    //Blow rings out
    //analogWrite(fanMotor, 255);
    delay(wait);
    //analogWrite(fanMotor, 0);
    Serial.println("one successful iteration");
  }

}
