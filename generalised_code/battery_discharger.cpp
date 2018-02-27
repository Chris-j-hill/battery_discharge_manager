
#include "battery_discharger.h"
//#include "softPwm.h"
#include "Arduino.h"

int num_battery_in_parallel = 0;
int analog0_pins[] = {A0, A2, A4};
int analog1_pins[] = {A1, A3, A5};
int bjt_pins[] = {9, 10, 11};
int mosfet_pins[] = {2, 3, 4, 5, 6, 7, 8, 12, 13};



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

void battery::update_values() {

  if (mosfet_pin_on < 0) { //if no battery is on, skip reading
    return;
  }

  analog0_reading = analogRead(analog0_pin);
  analog1_reading = analogRead(analog1_pin);

  //  voltage = ;
  //  current = ;

}
void battery::check_voltage() {  //for checking the voltage when the current is off

  for (int i = 0; i < QUEUE_SIZE; i++) { //turn off all mosfets
    digitalWrite(mosfet_pin[i], LOW);
  }
  analogWrite(bjt_pin, LOW); //force bjt off for reading

  digitalWrite(mosfet_pin[current_mosfet], HIGH);  //turn on current mosfet
  delay(50);  //delay to allow voltage to stabilise
  voltage = (analogRead(analog0_pin) * NOMINAL_VOLTAGE) / RANGE;  //take reading

  if (voltage < MINIMUM_VOLTAGE_TO_START_DISCHARGE) { // if value below starting voltage increment mosfet pin
    current_mosfet = (current_mosfet + 1) % QUEUE_SIZE;   //cycle through mosfet pins
  }
  else {
    discharge_this_cell = true;
    start_time = millis();
  }
}

void battery::read_inputs() {}

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


void battery::increment_mosfet() {}
void battery::config_resistance(double resistance) {}
void battery::bjt_off() {
  analogWrite(bjt_pin, LOW);
}

