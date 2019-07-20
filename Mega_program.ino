#include <Servo.h>   //including the servo library
//trig of ultrasonic sensor
int trig = 12;
//echo of ultrasonic sensor
int echo = 13;
Servo sg90;          //including a variable for servo named sg90
String mode = "2551900255";  //default mode is bluetooth

void setup() {
  //Bluetooth car set up
  pinMode(4,OUTPUT);   //left motors power
  pinMode(5,OUTPUT);   //left motors direction
  pinMode(6,OUTPUT);   //right motors power
  pinMode(7,OUTPUT);   //right motors direction

  //Line Tracker Set up
  #define l_sensor A0  //left sensor
  #define m_sensor A1  //middle sensor
  #define r_sensor A2  //right sensor
  #define fr_sensor A3  //far right sensor
  #define fl_sensor A4  // far left sensor

  pinMode(r_sensor, INPUT);
  pinMode(m_sensor, INPUT);
  pinMode(l_sensor, INPUT);
  pinMode(fl_sensor, INPUT);
  pinMode(fr_sensor, INPUT);

  //Object Avoidance Set up
  #define servo_pin A5  //for servor motor
  pinMode(trig, OUTPUT);
  pinMode(echo,INPUT);
  sg90.attach(servo_pin);  //Control pin A5 for servo
  Serial.begin(9600); 
}
void loop() {
  if (Serial.available() > 0) {
    mode = "";
    for(int i = 0; i < 5; ++i) {
      mode += Serial.read();
    }
  }
  if(mode == "2551900255") {
    Serial.print("Going into bluetooth\n");
    mode = bluetooth_car();
  }
  else if (mode == "2551910255") {
    Serial.print("Going into LT\n");
    mode = line_tracker();
  }
  else {  //mode == "2551920255"
    Serial.print("Going into OA\n");
    mode = obstacle_avoidance();
  }
}

// function for driving straight
void forward(char powermode) {
  if(powermode == 'L') {
  digitalWrite(4, HIGH);
  analogWrite(5, 140);
  digitalWrite(7, HIGH);  //for same direction
  analogWrite(6, 140);
  }
  else {
  digitalWrite(4, HIGH);
  analogWrite(5, 255);
  digitalWrite(7, HIGH);  //for same direction
  analogWrite(6, 255);  
  }
}
 
//function for reversing
void reverse() {
  digitalWrite(4, LOW);
  analogWrite(5, 255);
  digitalWrite(7, LOW);
  analogWrite(6, 255);
}
 
//function for turning left
void left() {
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
  analogWrite(5, 255);
  analogWrite(6, 255);
}
 
//function for turning right
void right() {
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
  analogWrite(5, 255);
  analogWrite(6, 255);
}
 
//function for stopping motors
void stop_motors() {
  digitalWrite(4, LOW);
  digitalWrite(7,LOW);
  analogWrite(5, 0);
  analogWrite(6, 0);
}

//function for ultrasonic distance measure
int US_distance() {
  //thats the sequence for ultrasonic sensor to start reading
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
   
  //here we got travel time of sonic wave
  int duration = pulseIn(echo, HIGH);
  //and here we calculate distance from it
  return (duration/2) / 29.1;
}

String array_to_string(int myarray[]) {
  String result;
  for(int k = 0; k < 5; ++k) {
    result += myarray[k];
  }
  return result;
}

//function for bluetooth control
String bluetooth_car() {
    int command[5];
    while(1) {
    if(Serial.available() > 0) {
      for(int i = 0; i < 5; ++i) {
          command[i] = Serial.read();
      }
    }
    Serial.print("The array so far is ");
    for(int i = 0; i < 5; ++i) {
      Serial.print(command[i]);
    }
    Serial.print("\nThe value of the command is =  ");
    Serial.print(command[2]);
    Serial.print("\n");
      
    if(array_to_string(command) == "255010255"){  //move forward(all motors rotate in forward direction) since we got "255010255"
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
    }
    else if(array_to_string(command) == "255020255"){  //move reverse (all motors rotate in reverse direction) since we got "255020255"
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
    }
    else if(array_to_string(command) == "255040255"){  //turn right (left side motors rotate in forward direction, right side motors doesn't rotate) since we got "255040255"
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    analogWrite(5, 255);
    analogWrite(6, 255);
    }
    else if(array_to_string(command) == "255030255"){  //turn left (right side motors rotate in forward direction, left side motors doesn't rotate) since we got "255030255"
      digitalWrite(4, LOW);
      digitalWrite(7, HIGH);
      analogWrite(5, 255);
      analogWrite(6, 255);
    } 
    else if(array_to_string(command) == "255000255"){  //STOP (all motors stop) since we got "255000255"
      stop_motors();
    }
    else if ((array_to_string(command) == "2551910255") || (array_to_string(command) == "2551920255")){
      break;
    }
  }
  return array_to_string(command);
}

//function for following line 
String line_tracker() {
  while(1) {
    if(Serial.available() > 0) {
      break;
    }
    if(!(digitalRead(fl_sensor)) && !(digitalRead(l_sensor)) && !(digitalRead(m_sensor)) && !(digitalRead(r_sensor)) && !(digitalRead(fr_sensor))) {  // stop
      Serial.p  rint("Condition true, i have stopped\n");
      stop_motors();
    }
    else if(!(digitalRead(fl_sensor))) {  //turn a greater left if extreme left sensor and near left sensor both are on the line
      while(!(digitalRead(fl_sensor)) || !(digitalRead(l_sensor))) {
        left();
      }
    }
    else if(!(digitalRead(fr_sensor))) {  //turn a greater right if extreme right sensor and near right sensor both are on the line
      while(!(digitalRead(fr_sensor)) || !(digitalRead(r_sensor))) {
        right();
      }
    }
    else if(digitalRead(r_sensor) && digitalRead(l_sensor)) {  // Move Forward
      forward('L');
    }
    else if(!(digitalRead(l_sensor)) && digitalRead(r_sensor)) {  // Turn left
      left();
    }
    else if(digitalRead(l_sensor) && !(digitalRead(r_sensor))) {  // turn right
      right();
    }
  }
  String change; 
  if(Serial.available() > 0) {
    for(int i = 0; i < 5; ++i) {
      change += Serial.read();
    }
  Serial.print("going out of LT and the mode value is ");
  Serial.print(change);
  Serial.print("\n");
  return change;
  }
}

//function for obstacle collision avoidance
String obstacle_avoidance() {
  while(1) {
    sg90.write(90);     // moving the servo at 90 degree
    delay(500);        //wait for 0.5 seconds to turn 90 degrees back to original position
  
    if(US_distance() > 17.5){
      //move forward by 150 ms
      forward('A');  //go full power not limited (the one for line tracking)
      delay(150);
    }
    else {
      stop_motors();
      int leftD, rightD;
      sg90.write(0);    // moving the servo at 0 degree
      delay(500);        // wait for 0.5 second since only 90degree turn needed
      rightD = US_distance();
      sg90.write(180);    // moving the servo at 180 degree
      delay(1000);        // wait for 1 second since have to turn 180 degrees
      leftD = US_distance();
      if(rightD > leftD) {
        right();
        delay(320);
      }
      else {
        left();
        delay(320);
      }
      stop_motors();  //to stop the turn
    }
    if(Serial.available() > 0) {
        break;
    }
  }
  String change;
  if(Serial.available() > 0) {
    for(int i = 0; i < 5; ++i) {
      change += Serial.read();
    }
  Serial.print("going out of OA and the mode value is ");
  Serial.print(change);
  Serial.print("\n");
  return change;
  }
}
