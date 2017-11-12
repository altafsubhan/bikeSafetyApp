#include <SoftwareSerial.h>
#include <Timer.h>

SoftwareSerial BT(4, 2);
String command = "";
Timer t;

const int TRIG_PIN = 12;
const int ECHO_PIN = 11;
const int LEFT_PIN = 7;  
const int RIGHT_PIN = 5 ;  
const int CENTER_PIN = 6;  

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  BT.begin(9600);
}

//Blink twice every second
void turnRight(){
  for (int i = 0; i < 6; i++){
    digitalWrite(RIGHT_PIN, HIGH);
    delay(800);
    digitalWrite(RIGHT_PIN, LOW);
    delay(200);
  }
  //t.pulse(RIGHT_PIN, 500, HIGH);
}

//Blink twice every second
void turnLeft(){
  for (int i = 0; i < 6; i++){
    digitalWrite(LEFT_PIN, HIGH);
    delay(800);
    digitalWrite(LEFT_PIN, LOW);
    delay(200);
  }
  //t.pulse(LEFT_PIN, 500, HIGH);
}

//Blink twice every second
void caution(){
  for (int i = 0; i < 6; i++){
    digitalWrite(LEFT_PIN, HIGH);
    digitalWrite(RIGHT_PIN, HIGH);
    digitalWrite(CENTER_PIN, HIGH);
    delay(750);
    digitalWrite(LEFT_PIN, LOW);
    digitalWrite(RIGHT_PIN, LOW);
    digitalWrite(CENTER_PIN, LOW);
    delay(250);
  }
  //t.pulse(RIGHT_PIN, 500, HIGH);
  //t.pulse(LEFT_PIN, 500, HIGH);
  //t.pulse(CENTER_PIN, 500, HIGH);
}

void brake(){
  //for (int i = 0; i < 4; i++){
    digitalWrite(CENTER_PIN, HIGH);
    delay(4000);
    digitalWrite(CENTER_PIN, LOW);
    //delay(250);
  //}
}

void turnOffBrakes(){
  digitalWrite(CENTER_PIN, LOW);
}

void loop() {
  //t.update();
  while (BT.available()) {
    char in = BT.read();
    Serial.println(in);

    if(in == '1'){
      turnRight();
    } else if (in=='2'){
      turnLeft();
    } else if (in=='3'){
      brake();
    } else if (in=='4'){
      caution();
    }
      delay(100);
  }
    // Get SONAR input
    digitalWrite(TRIG_PIN, LOW);
    delay(100);
  
    digitalWrite(TRIG_PIN, HIGH);
    delay(10);
    digitalWrite(TRIG_PIN, LOW);
  
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration*0.034/2;

    if (distance < 10){
      BT.print('@'); 
      caution();
      Serial.println("Sent!");
    }

    //accelerometer stuff
}

