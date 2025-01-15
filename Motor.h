#ifndef DINAMO_HANDLER
#define DINAMO_HANDLER

// Define control pins for the existing RC car module  
#define CONTROL_PIN_FORWARD 15  
#define CONTROL_PIN_BACKWARD 13
#define CONTROL_PIN_LEFT 2
#define CONTROL_PIN_RIGHT 14


void handleMotorControl(String command, bool state);

void updateMotorStates();

#endif