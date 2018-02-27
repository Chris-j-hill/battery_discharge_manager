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
  bat1.update_values();
}
