#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 7

int prevstate = 0;
int state = 0;
SoftwareSerial bluetoothSerial(rxPin, txPin); // RX, TX

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  // put your setup code here, to run once:

}

void loop() {
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
      Serial.println("UP TRUE");
      break;
    case 38:
      Serial.println("UP FALSE");
      break;
    case 37:
      Serial.println("DOWN TRUE");
      break;
    case 36:
      Serial.println("DOWN FALSE");
      break;
  }
}
