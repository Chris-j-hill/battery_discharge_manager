
#ifndef BATT_DISCHARGER_H
#define BATT_DISCHARGER_H

#define QUEUE_SIZE 4
#define NUM_QUEUES 4
#define RANGE 1024
#define NOMINAL_VOLTAGE 5
#define MINIMUM_VOLTAGE_TO_START_DISCHARGE 3.7
#define MINIMUM_VOLTAGE 3
#define DISCHARGE_CURRENT 1000    //millisamps to discharge at

class battery{

  public:
  battery();

  void update_values();
  void check_voltage();   //for checking the voltage when the current is off
  void read_inputs();
  void set_pwm();
  void increment_mosfet();
  void config_resistance(double value);
  void bjt_off();
  void config_mosfet_voltage_drop(double queue_mosfets[QUEUE_SIZE]);
  void print_data();
  void print_pins();

  bool discharge_this_cell = false;
  double voltage;
  double current;
  int start_time;
  int milliamp_hours[QUEUE_SIZE];
  int current_mosfet;
  double cell_cut_off_voltage[QUEUE_SIZE];  
  
  
  private:
  double resistance;


  int analog0_reading;
  int analog1_reading;
  int bjt_value;
  int mosfet_pin_on;      
  int battery_capacities[QUEUE_SIZE];
  double mosfet_voltage_drop[QUEUE_SIZE];
  int analog0_pin;
  int analog1_pin;
  int mosfet_pin[QUEUE_SIZE];
  
  int bjt_pin;
  int bjt_pwm_val =0;
      
};

#endif

