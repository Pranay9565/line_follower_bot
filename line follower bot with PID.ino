// === Pin Definitions ===
int enL = 2;
int enR = 3;

int L_front = 4;
int L_back = 5;
int R_front = 6;
int R_back = 7;

int ir_r2 = 8;
int ir_r1 = 9;
int ir_m = 10;
int ir_l1 = 11;
int ir_l2 = 12;

// === PID constants (tune these) ===
float Kp = 30;    // Proportional
float Ki = 0;     // Integral
float Kd = 20;    // Derivative

// === PID variables ===
float error = 0, prevError = 0, integral = 0;
int baseSpeed = 150;   // Base motor PWM speed (0–255)

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

  analogWrite(enL, baseSpeed);
  analogWrite(enR, baseSpeed);
}

// === MAIN LOOP ===
void loop() {
  // Invert readings: line (black) = 1, background (white) = 0
  int s[5];
  s[0] = !digitalRead(ir_l2);
  s[1] = !digitalRead(ir_l1);
  s[2] = !digitalRead(ir_m);
  s[3] = !digitalRead(ir_r1);
  s[4] = !digitalRead(ir_r2);

  int weight[5] = {-2, -1, 0, 1, 2};

  float sum = 0;
  float count = 0;
  for (int i = 0; i < 5; i++) {
    sum += s[i] * weight[i];
    count += s[i];
  }

  if (count == 0) {
    // Line lost, stop or keep last direction
    Stop();
    return;
  }

  error = sum / count;

  // === PID Calculations ===
  integral += error;
  float derivative = error - prevError;
  float correction = Kp * error + Ki * integral + Kd * derivative;

  prevError = error;

  // === Adjust Motor Speeds ===
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  // Constrain to 0–255
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  moveMotors(leftSpeed, rightSpeed);
}

// === FUNCTIONS ===

void moveMotors(int leftPWM, int rightPWM) {
  analogWrite(enL, leftPWM);
  analogWrite(enR, rightPWM);

  digitalWrite(L_front, HIGH);
  digitalWrite(L_back, LOW);
  digitalWrite(R_front, HIGH);
  digitalWrite(R_back, LOW);
}

void Stop() {
  digitalWrite(L_front, LOW);
  digitalWrite(L_back, LOW);
  digitalWrite(R_front, LOW);
  digitalWrite(R_back, LOW);
}
