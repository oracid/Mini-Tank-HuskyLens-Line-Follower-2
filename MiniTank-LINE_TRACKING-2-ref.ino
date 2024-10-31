// 25/01/2022 - MiniTank line tracking with HuskyLens #2
#include <HUSKYLENS.h>
#include <Servo.h>
void(* resetFunc) (void) = 0;       // soft reset function
Servo sR,sL;                        // right servo and left servo
int R, L, d;                        // right servo value, left servo value
HUSKYLENS huskylens; int ID1=1;     // HuskyLens objet

void setup() {
  Serial.begin(9600);
  sR.attach(3);sR.write(90);        // right servo initialization
  sL.attach(4);sL.write(90);        // left servo initialization
  Wire.begin();
  while (!huskylens.begin(Wire)) {Serial.print("\n Check I2C"); delay(100);}
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Switch the algorithm to line tracking.
}

void loop() {
  huskylens.request(ID1);
  if(!huskylens.available()){if ( d=='R' ) { sL.write(0);  sR.write(0);   return;}} // turning right
  if(!huskylens.available()){if ( d=='L' ) { sL.write(180);sR.write(180); return;}} // turning left
  HUSKYLENSResult result = huskylens.read();
  int err=map(result.xTarget,0,320,-90,90);                                   // getting and maping error
  if ( err < 0) { L=0-err; R=180; d='L'; }  else  { L=0; R=180-err; d='R'; }  // error makes turning left or right
  sL.write(L);  sR.write(R);                                                  // left and right servos order
}
