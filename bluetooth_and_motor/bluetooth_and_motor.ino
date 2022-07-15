#include <SoftwareSerial.h>

//channel pins for encoder values
int channelA = 5;
int channelB = 4;
int pwmPin = 6;

//output pins to control motor input
int in1Pin = 10;
int in2Pin = 9;

//encoder channel values
int valA= 0;
int valB= 0;

//for counting purposes
int valAPrev=valA;

//motor pwm duty cycle
int motorVal = 200;

//touch sensor pin NOTE CHANGE THIS
int touchPin = 7;

int motorVals[] = {125,150,175, 200, 225,250};
int motorIndex = 0;
int bufIndex=0;
int buf[30];

//motor direction
int dir = 0;
int brightness = 0;
//
volatile int pulses =0 ;

//timing
long previousMillis = 0;

long previousMillis5 = 0;


int done = 0;

int prevPulse = 0;



#define rxPin 2
#define txPin 3

int prevstate = 0;
int state = 0;
SoftwareSerial bluetoothSerial(rxPin, txPin); // RX, TX

void onTouch(){
    analogWrite(pwmPin, 0);
    Serial.print("HELLO");

}
void setup() {
  //BLUETOOTH SETUP
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  //MOTOR SETUP
  pinMode(channelA, INPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(touchPin, INPUT);

  //attachInterrupt(digitalPinToInterrupt(channelB), count_event, RISING);
  attachInterrupt(digitalPinToInterrupt(touchPin), onTouch, RISING);

  // put your setup code here, to run once:

}

void loop() {

  if (digitalRead(touchPin) == HIGH){
    Serial.print("HIGH");
  }

  digitalWrite(in1Pin, dir);
  digitalWrite(in2Pin, !dir);
  while (bluetoothSerial.available()) {
    state = bluetoothSerial.read();
    //Serial.println(state);
  }
  if (state != prevstate)
  {
    //Serial.println(state);
    prevstate = state;
    handleState();


  }
  //Serial.println("State: " + state);

  // put your main code here, to run repeatedly:

}

void handleState() {
  switch (state) {
    case 39:
      dir = 0; 
      Serial.println("UP TRUE");
      analogWrite(pwmPin, motorVal);

      break;
    case 38:
      Serial.println("UP FALSE");
      analogWrite(pwmPin, 0);

      break;
    case 37:
      Serial.println("DOWN TRUE");
      dir =1;
      analogWrite(pwmPin, motorVal);

      break;
    case 36:
      Serial.println("DOWN FALSE");
      analogWrite(pwmPin, 0);

      break;
  }
}
void count_event(){
  pulses++;
}
