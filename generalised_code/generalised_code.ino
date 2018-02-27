#include "battery_discharger.h"




const double resistor[3] = {0.5, 0.5, 0.5};

battery bat1; //three queues
battery bat2;
battery bat3;


void setup() {
  // put your setup code here, to run once:

  bat1.config_resistance(resistor[0]);
  bat2.config_resistance(resistor[1]);
  bat3.config_resistance(resistor[2]);

}

void loop() {
  // put your main code here, to run repeatedly:
  // bat1
  if (bat1.discharge_this_cell) {
    bat1.read_inputs(); //get input values
    
    if (bat1.voltage <= MINIMUM_VOLTAGE) {  // if discharged, stop current, log milliamp hours
      bat1.bjt_off();
      bat1.discharge_this_cell = false;
      bat1.milliamp_hours[bat1.current_mosfet] = ((millis() - bat1.start_time) * (DISCHARGE_CURRENT) / (1000 * 60 * 60));

    }
    //  else if(){}//not drawing full current?
    else {
      //discharging, manage current
      bat1.set_pwm();
    }

  }
  else{
    bat1.check_voltage(); //check voltage of batteries, start discharge if above minimum value
  }




  
  }
