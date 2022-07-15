//channel pins for encoder values
int channelA = 3;
int channelB = 2;
int pwmPin = 5;

//output pins to control motor input
int in1Pin = 10;
int in2Pin = 9;

//encoder channel values
int valA= 0;
int valB= 0;

//for counting purposes
int valAPrev=valA;

//motor pwm duty cycle
int motorVal = 100;

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

void count_event(){
  pulses++;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   
  pinMode(channelA, INPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(channelB), count_event, RISING);


}

void loop() {
  // put your main code here, to run repeatedly:  
  unsigned long currentMillis = millis();


  valA = digitalRead(channelA);
  valB = digitalRead(channelB);
  
  unsigned long delta = currentMillis - previousMillis;
  unsigned long delta5 = currentMillis - previousMillis5;
  if (bufIndex < 30){

    if ((delta) > 1000){
      //1 second has elapsed, so record the cycle count
      buf[bufIndex] = pulses;      
      if (delta5 > 5000){ 
        //we've taken 5 samples, so we want to increment motor counter
        motorIndex++;
       


      }
      pulses = 0;
      bufIndex++;
      motorVal = motorVals[motorIndex];
      analogWrite(pwmPin, motorVal);
      //delay(500); //we pause here to let the motor reach a new speed.
     previousMillis = currentMillis;
      if (delta5>5000){
        previousMillis5 = currentMillis;
      }
    }
    analogWrite(pwmPin, motorVal);
    digitalWrite(in1Pin, dir);
    digitalWrite(in2Pin, !dir);
    


  }
  else{
  // if we exceed buffer index we are done
    analogWrite(pwmPin, 0);
    for (int i = 0 ; i < 30 && !done; i++){
      Serial.print("pwm: ");
      Serial.print(motorVals[i/5]);
      Serial.print(" hz: ");
      Serial.print(buf[i]);
      Serial.println();
    }
    done = 1;
    
  }
  /*Serial.print("cycles:");
    Serial.print(cycles);
    Serial.print("ChannelA:");
    Serial.print(valA);
    Serial.print(",");
    Serial.print("ChannelB:");

    Serial.print(valB);
    Serial.print(",");

    Serial.println("Min:0,Max:1.5");*/









}
