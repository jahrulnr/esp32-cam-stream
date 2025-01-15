#include <Arduino.h>  
#include "Motor.h"
  
bool forwardActive = false;  
bool backwardActive = false;  
bool leftActive = false;  
bool rightActive = false;  

void handleMotorControl(String command, bool state) {  
    // Update the state of the motors based on the command  
    if (command == "forward") {  
        forwardActive = state;  
        backwardActive = false; // Prevent conflicting commands  
    } else if (command == "backward") {  
        backwardActive = state;  
        forwardActive = false; // Prevent conflicting commands  
    } else if (command == "left") {  
        leftActive = state;  
        rightActive = false; // Prevent conflicting commands  
    } else if (command == "right") {  
        rightActive = state;  
        leftActive = false; // Prevent conflicting commands  
    } else if (command == "stopA") {  
        // Stop all motors  
        forwardActive = false;          
        backwardActive = false;  
    } else if (command == "stopB") {
        leftActive = false;  
        rightActive = false;  
    }
}  
  
void updateMotorStates() {    
    // Control logic for smooth movement    
    if (forwardActive && leftActive) {    
        // Move forward and turn left    
        digitalWrite(CONTROL_PIN_FORWARD, HIGH);    
        digitalWrite(CONTROL_PIN_BACKWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, HIGH);    
        digitalWrite(CONTROL_PIN_RIGHT, LOW);    
    } else if (forwardActive && rightActive) {    
        // Move forward and turn right    
        digitalWrite(CONTROL_PIN_FORWARD, HIGH);    
        digitalWrite(CONTROL_PIN_BACKWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, LOW);    
        digitalWrite(CONTROL_PIN_RIGHT, HIGH);    
    } else if (backwardActive && leftActive) {    
        // Move backward and turn left    
        digitalWrite(CONTROL_PIN_BACKWARD, HIGH);    
        digitalWrite(CONTROL_PIN_FORWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, HIGH);    
        digitalWrite(CONTROL_PIN_RIGHT, LOW);    
    } else if (backwardActive && rightActive) {    
        // Move backward and turn right    
        digitalWrite(CONTROL_PIN_BACKWARD, HIGH);    
        digitalWrite(CONTROL_PIN_FORWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, LOW);    
        digitalWrite(CONTROL_PIN_RIGHT, HIGH);    
    } else if (forwardActive) {    
        // Move forward only    
        digitalWrite(CONTROL_PIN_FORWARD, HIGH);    
        digitalWrite(CONTROL_PIN_BACKWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, LOW);    
        digitalWrite(CONTROL_PIN_RIGHT, LOW);    
    } else if (backwardActive) {    
        // Move backward only    
        digitalWrite(CONTROL_PIN_BACKWARD, HIGH);    
        digitalWrite(CONTROL_PIN_FORWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, LOW);    
        digitalWrite(CONTROL_PIN_RIGHT, LOW);    
    } else if (leftActive) {    
        // Turn left only    
        digitalWrite(CONTROL_PIN_FORWARD, LOW);    
        digitalWrite(CONTROL_PIN_BACKWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, HIGH);    
        digitalWrite(CONTROL_PIN_RIGHT, LOW);    
    } else if (rightActive) {    
        // Turn right only    
        digitalWrite(CONTROL_PIN_FORWARD, LOW);    
        digitalWrite(CONTROL_PIN_BACKWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, LOW);    
        digitalWrite(CONTROL_PIN_RIGHT, HIGH);    
    } else {    
        // Default to stop if no active commands    
        digitalWrite(CONTROL_PIN_FORWARD, LOW);    
        digitalWrite(CONTROL_PIN_BACKWARD, LOW);    
        digitalWrite(CONTROL_PIN_LEFT, LOW);    
        digitalWrite(CONTROL_PIN_RIGHT, LOW);    
    }    
}  