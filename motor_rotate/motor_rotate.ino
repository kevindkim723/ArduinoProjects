//channel pins for encoder values
int channelA = 3;
int channelB = 2;
int pwmPin = 5;

//output pins to control motor input
int in1Pin = 10;
int in2Pin = 9;

//encoder channel values
int valA = 0;
int valB = 0;

//for counting purposes
int valAPrev = valA;

//motor pwm duty cycle
int motorVal = 200;

int motorVals[] = {125, 150, 175, 200, 225, 250};
int motorIndex = 0;
int bufIndex = 0;
int buf[30];

//motor direction
int dir = 0;
int brightness = 0;
//
volatile int pulses = 0 ;

//timing
long previousMillis = 0;

long previousMillis5 = 0;


int done = 0;

int prevPulse = 0;

void count_event() {
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
  if (pulses >= 280) {
    analogWrite(pwmPin, 0);
    
  }
  else{
   analogWrite(pwmPin, motorVal);
   

  }
  digitalWrite(in1Pin, dir);
  digitalWrite(in2Pin, !dir);
  
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
