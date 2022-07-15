int analogIn = A0;
int LEDpin = 7;
int counter = 0;
const int bufsize = 10;
const int slopebufsize = 100;

int buf[bufsize];
int slope;
int slopebuf[slopebufsize];
int i = 0;
bool done = false;





void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(analogIn, INPUT);
  pinMode(LEDpin, OUTPUT);

}

void loop() {
  if (i < slopebufsize) {
    Serial.println(i);

    // put your main code here, to run repeatedly:
    int value = analogRead(analogIn);
    /*Serial.print(0); // To freeze the lower limit
    Serial.print(" ");
    Serial.print(1000); // To freeze the upper limit
    Serial.print(" ");
    Serial.print("Analog value : ");
    Serial.println(value);*/
    delay(3);
    //delay(100);
    for (int k  = 0; k < bufsize - 1; k++)
    {
      buf[k] = buf[k + 1];
    }
    buf[bufsize - 1] = value;
    counter++;
    if (counter > bufsize) {
      slope = getSlope(buf, bufsize);
      slopebuf[i] = slope;
      i++;
      counter = 0;
    }
  }
  else {
    if (!done) {
      for (int j = 0 ; j < slopebufsize; j++) {
        Serial.println(slopebuf[j]);
      }
      done = 1;

    }

  }



}
int getSlope(int* buf, int bufsize) {
  int slope = 0;
  int y_0 = buf[0];
  for (int i = 1 ; i < bufsize; i++) {
    slope += (buf[i] - y_0);
  }
  slope = (int) (slope / 10);
  return slope;
}
