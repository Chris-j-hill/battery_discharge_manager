
//#define DEBUG_MODE      // used to measure the voltage drop accross the resistor for different pwm values
int pwm_val = 180;
int analog0 = 0;
int analog1 = 0;
byte increment = 1;
double resistance = 0.517;
double current = 0.00;
double voltage = 0.00;
double range = 1024.00;
double target_current = 1.5;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, OUTPUT);
  analogWrite(2, pwm_val);
  Serial.begin(115200);
}
#ifdef DEBUG_MODE
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() != 0) {
    char input = Serial.read();
    if (input == 'w') {
      if (pwm_val < 255 - increment)
        pwm_val = pwm_val + increment;
      analogWrite(2, pwm_val);
    }
    else if (input == 's') {
      if (pwm_val > 0 + increment)
        pwm_val = pwm_val - increment;
      analogWrite(2, pwm_val);

    }
  }

  analog0 = analogRead(A0);
  analog1 = analogRead(A1);

  voltage = ((analog0 - analog1) * 5.0) / range;
  current = voltage / resistance;

  Serial.print("pwm value:");
  Serial.print(pwm_val);
  Serial.print("\t analog difference:");
  Serial.print(analog0 - analog1);
  Serial.print("\t voltage drop:");
  Serial.print(voltage);
  Serial.print("\t current:");
  Serial.print(current);

  Serial.println();
  delay(100);
}

#else
void loop() {

  analog0 = analogRead(A0);
  analog1 = analogRead(A1);

  voltage = ((analog0 - analog1) * 5.0) / range;
  current = voltage / resistance;

  if (current < target_current) {
    pwm_val++;
    analogWrite(2, pwm_val);
    if (pwm_val > 254)
      pwm_val = 255;
    else
      pwm_val++;
    analogWrite(2, pwm_val);
  }

  else if (current > target_current) {

    if (pwm_val < 1)
      pwm_val = 0;
    else
      pwm_val--;
    analogWrite(2, pwm_val);
  }

  Serial.print("pwm value:");
  Serial.print(pwm_val);
  Serial.print("\t current:");
  Serial.print(current);

  Serial.println();
  delay(100);
}
#endif
