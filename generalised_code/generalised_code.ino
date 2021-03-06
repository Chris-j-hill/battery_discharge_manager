#include "battery_discharger.h"

const double resistor[] = {1.5, 1.5, 1.5, 1.5};
struct Mosfet {

  double queue1[QUEUE_SIZE] = {0.7, 0.7, 0.7, 0.7};
  double queue2[QUEUE_SIZE] = {0.7, 0.7, 0.7, 0.7};
  double queue3[QUEUE_SIZE] = {0.7, 0.7, 0.7, 0.7};
  double queue4[QUEUE_SIZE] = {0.7, 0.7, 0.7, 0.7};

};
Mosfet mosfet;

battery bat1; //four queues
battery bat2;
battery bat3;
battery bat4;

void setup() {

  Serial.begin(115200);
  bat1.config_resistance(resistor[0]);
  bat2.config_resistance(resistor[1]);
  bat3.config_resistance(resistor[2]);
  bat4.config_resistance(resistor[3]);

  bat1.config_mosfet_voltage_drop(mosfet.queue1);
  bat2.config_mosfet_voltage_drop(mosfet.queue2);
  bat3.config_mosfet_voltage_drop(mosfet.queue3);
  bat4.config_mosfet_voltage_drop(mosfet.queue4);

  bat1.print_pins();
  bat2.print_pins();
  bat3.print_pins();
  bat4.print_pins();
  Serial.println();

}

void loop() {

  manage_bat1();
  manage_bat2();
  manage_bat3();
  manage_bat4();

  bat1.print_data();
  bat2.print_data();
  bat3.print_data();
  bat4.print_data();
  Serial.println("==========================================================================================");
  delay(300);

}


void manage_bat1() {
  if (bat1.discharge_this_cell) {
    bat1.read_inputs(); //get input values

    if (bat1.voltage <= bat1.cell_cut_off_voltage[bat1.current_mosfet]) {  // if discharged, stop current, log milliamp hours
      bat1.bjt_off();
      bat1.discharge_this_cell = false;
      bat1.milliamp_hours[bat1.current_mosfet] = ((millis() - bat1.start_time) * (DISCHARGE_CURRENT) / (1000 * 60 * 60));

    }

    else {
      //discharging, manage current
      bat1.set_pwm();
    }
  }
  else {
    bat1.check_voltage(); //check voltage of batteries, start discharge if above minimum value
  }
}

void manage_bat2() {
  if (bat2.discharge_this_cell) {
    bat2.read_inputs(); //get input values

    if (bat2.voltage <= bat2.cell_cut_off_voltage[bat2.current_mosfet]) {  // if discharged, stop current, log milliamp hours
      bat2.bjt_off();
      bat2.discharge_this_cell = false;
      bat2.milliamp_hours[bat2.current_mosfet] = ((millis() - bat2.start_time) * (DISCHARGE_CURRENT) / (1000 * 60 * 60));

    }

    else {
      //discharging, manage current
      bat2.set_pwm();
    }
  }
  else {
    bat2.check_voltage(); //check voltage of batteries, start discharge if above minimum value
  }
}

void manage_bat3() {
  if (bat3.discharge_this_cell) {
    bat3.read_inputs(); //get input values

    if (bat3.voltage <= bat3.cell_cut_off_voltage[bat3.current_mosfet]) {  // if discharged, stop current, log milliamp hours
      bat3.bjt_off();
      bat3.discharge_this_cell = false;
      bat3.milliamp_hours[bat3.current_mosfet] = ((millis() - bat3.start_time) * (DISCHARGE_CURRENT) / (1000 * 60 * 60));

    }

    else {
      //discharging, manage current
      bat3.set_pwm();
    }
  }
  else {
    bat3.check_voltage(); //check voltage of batteries, start discharge if above minimum value
  }
}

void manage_bat4() {
  if (bat4.discharge_this_cell) {
    bat4.read_inputs(); //get input values

    if (bat4.voltage <= bat4.cell_cut_off_voltage[bat4.current_mosfet]) {  // if discharged, stop current, log milliamp hours
      bat4.bjt_off();
      bat4.discharge_this_cell = false;
      bat4.milliamp_hours[bat4.current_mosfet] = ((millis() - bat4.start_time) * (DISCHARGE_CURRENT) / (1000 * 60 * 60));

    }

    else {
      //discharging, manage current
      bat4.set_pwm();
    }
  }
  else {
    bat4.check_voltage(); //check voltage of batteries, start discharge if above minimum value
  }
}
