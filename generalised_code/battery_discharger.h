
#ifndef BATT_DISCHARGER_H
#define BATT_DISCHARGER_H

#define QUEUE_SIZE 3
#define RANGE 1024
#define NOMINAL_VOLTAGE 5
#define MINIMUM_VOLTAGE_TO_START_DISCHARGE 3.7


class battery{

  public:
  battery();

  void update_values();
  void check_voltage();   //for checking the voltage when the current is off
  void read_inputs();
  void set_pwm();
  void increment_mosfet();
  void config_resistance(double resistance);


  private:
  int voltage;
  int current;
  int resistance;
  int amp_hours;

  int start_time();
  int analog0_reading;
  int analog1_reading;
  int bjt_value;
  int mosfet_pin_on;      
  int battery_capacities[QUEUE_SIZE];

  int analog0_pin;
  int analog1_pin;
  int mosfet_pin[QUEUE_SIZE];
  int current_mosfet;
  int bjt_pin;
  bool discharge_this_cell = false;
      
};

#endif

