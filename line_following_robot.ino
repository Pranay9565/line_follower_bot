int enL = 2;    // enable pin for left motor
int enR = 3;    // enable pin for right motor

int L_front = 4;    // left motor forward drive pin
int L_back = 5;   // left motor backward drive pin
int R_front = 6;    // right motor forward drive pin
int R_back = 7;   // right motor backward drive pin

int ir_r2 = 8;    // right most ir sensor
int ir_r1 = 9;    //right ir sensor
int ir_m = 10;    // middle ir sensor
int ir_l1 = 11;   //left ir sensor
int ir_l2 = 12;   //left most ir sensor


void setup() {

  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);

  pinMode(L_front, OUTPUT);
  pinMode(L_back, OUTPUT);
  pinMode(R_front, OUTPUT);
  pinMode(R_back, OUTPUT);

  pinMode(ir_r2, INPUT);
  pinMode(ir_r1, INPUT);
  pinMode(ir_m, INPUT);
  pinMode(ir_l1, INPUT);
  pinMode(ir_l2, INPUT);

}

void loop() {

  digitalWrite(enL, HIGH);
  digitalWrite(enR, HIGH);
  if(digitalRead(ir_m) == 0){
    Forward(); // if Middle Sensor is Black then it moves straight
    }
  if((digitalRead(ir_r1) == 1)&&(digitalRead(ir_l1) == 0)){
    TurnRight();
    } //if Right Sensor is Black and Left Sensor is White then it will call turn Right function  

  if((digitalRead(ir_r1) == 0)&&(digitalRead(ir_l1) == 1)){
    TurnLeft();
    }  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function

  if((digitalRead(ir_r1) == 1)&&(digitalRead(ir_r2) == 1)&&(digitalRead(ir_m) == 0)){
    Stop();
    } //if Right Sensor and Left Sensor are at Black color then it will call Stop function

}



/*FUNCTIONS FOR TURNING THE ROBOT*/

void Forward(){
  digitalWrite(L_front, HIGH);
  digitalWrite(R_front, HIGH);
  digitalWrite(L_back, LOW);
  digitalWrite(R_back, LOW);
}

void TurnLeft(){
  digitalWrite(L_front, LOW);
  digitalWrite(R_front, HIGH);
  digitalWrite(L_back, HIGH);
  digitalWrite(R_back, LOW);
}

void TurnRight(){
  digitalWrite(L_front, HIGH);
  digitalWrite(R_front, LOW);
  digitalWrite(L_back, LOW);
  digitalWrite(R_back, HIGH);
}

void Stop(){ //stop

digitalWrite(L_front, LOW); //Right Motor forword Pin 
digitalWrite(L_back, LOW); //Right Motor backword Pin 
digitalWrite(R_front, LOW); //Left Motor backword Pin 
digitalWrite(R_back, LOW); //Left Motor forword Pin 

}