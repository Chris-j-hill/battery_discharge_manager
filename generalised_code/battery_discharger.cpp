
#include "battery_discharger.h"
//#include "softPwm.h"
#include "Arduino.h"

int num_battery_in_parallel = 0;
int analog0_pins[QUEUE_SIZE] = {A0, A2, A4, A6};
int analog1_pins[QUEUE_SIZE] = {A1, A3, A5, A7};
int bjt_pins[QUEUE_SIZE] = {2,3,4,5};
int mosfet_pins[QUEUE_SIZE*NUM_QUEUES] = {22,23,24,25,   26,27,28,29,   30,31,32,33,   34,35,35,36};


battery::battery() {

  int i = 0;

  analog0_pin = analog0_pins[num_battery_in_parallel];
  analog1_pin = analog1_pins[num_battery_in_parallel];
  bjt_pin = bjt_pins[num_battery_in_parallel];

  for (i = 0; i < QUEUE_SIZE; i++)
    mosfet_pin[i] = mosfet_pins[num_battery_in_parallel * QUEUE_SIZE + i];

  //  init pins
  pinMode(bjt_pin, OUTPUT);
  pinMode(analog0_pin, OUTPUT);
  pinMode(analog1_pin, OUTPUT);

  for (i = 0; i < QUEUE_SIZE; i++)
    pinMode(mosfet_pins[i], OUTPUT);


  num_battery_in_parallel++;  //increment for next instanciation

}

void battery::check_voltage() {  //for checking the voltage when the current is off

  for (int i = 0; i < QUEUE_SIZE; i++) { //turn off all mosfets
    digitalWrite(mosfet_pin[i], LOW);
  }
  analogWrite(bjt_pin, LOW); //force bjt off for reading

  digitalWrite(mosfet_pin[current_mosfet], HIGH);  //turn on current mosfet
  delay(20);  //delay to allow voltage to stabilise
  voltage = (double)(analogRead(analog0_pin) * NOMINAL_VOLTAGE) / RANGE;  //take reading
  voltage = voltage+mosfet_voltage_drop[current_mosfet];
  
  if (voltage < MINIMUM_VOLTAGE_TO_START_DISCHARGE) { // if value below starting voltage increment mosfet pin
    current_mosfet = (current_mosfet + 1) % QUEUE_SIZE;   //cycle through mosfet pins
  }
  else {
    discharge_this_cell = true;
    start_time = millis();
  }
}

void battery::read_inputs() {

  if (mosfet_pin_on < 0) { //if no battery is on, skip reading
    return;
  }

  analog0_reading = analogRead(analog0_pin);
  analog1_reading = analogRead(analog1_pin);

  voltage = (double)(analog0_reading * NOMINAL_VOLTAGE) / RANGE;
  voltage = voltage+mosfet_voltage_drop[current_mosfet];
  current = (double)((analog0_reading - analog1_reading) * NOMINAL_VOLTAGE) / RANGE;
}

void battery::set_pwm() {
  if (current < DISCHARGE_CURRENT) {
    if (bjt_pwm_val > 254)
      bjt_pwm_val = 255;
    else
      bjt_pwm_val++;
    analogWrite(bjt_pin, bjt_pwm_val);
  }

  else if (current > DISCHARGE_CURRENT) {
    if (bjt_pwm_val < 1)
      bjt_pwm_val = 0;
    else
      bjt_pwm_val--;
    analogWrite(bjt_pin, bjt_pwm_val);
  }
}

void battery::config_resistance(double value) {
  resistance = value;
  }
  
void battery::bjt_off() {
  analogWrite(bjt_pin, LOW);
}

void battery::config_mosfet_voltage_drop(double queue_mosfets[QUEUE_SIZE]) {
  for (int i = 0; i < QUEUE_SIZE; i++){
    mosfet_voltage_drop[i] = queue_mosfets[i];
    cell_cut_off_voltage[i] = MINIMUM_VOLTAGE - queue_mosfets[i];
  }
}

void battery::print_data(){
  
  Serial.print("Mosfet:");
  Serial.print(current_mosfet);
  Serial.print("\t analog0:");
  Serial.print(analog0_reading);
  Serial.print("\t analog1:");
  Serial.print(analog1_reading);
  Serial.print("\t Current:");
  Serial.print(current);
  Serial.print("\t V_bat:");
  Serial.print(voltage);
  Serial.print("\t mAh:");
  Serial.print(milliamp_hours[current_mosfet]);
  Serial.print("\t pwm_value:");
  Serial.print(bjt_pwm_val);
  
  Serial.println();
}

void battery::print_pins(){

  Serial.print("analog0:");
  Serial.print(analog0_pin);
  Serial.print("\t analog1:");
  Serial.print(analog1_pin);
  
  for(int i=0;i<QUEUE_SIZE;i++){
    Serial.print("\t mosfet ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(mosfet_pin[i]);
  }

  Serial.print("\t bjt pin:");
  Serial.print(bjt_pin);
  Serial.println();
}

