#include <Arduino.h>  
#include "CameraConfig.h"  
#include "NetworkConfig.h"  
#include "WebSocketHandler.h" 
#include "WebServer.h" 
#include "Motor.h"
  
/**
 * @brief Setup function to initialize the ESP32-CAM.
 * 
 * This function performs the following initializations:
 * - Initializes serial communication at 115200 baud rate.
 * - Sets the LED flashlight pin mode to OUTPUT.
 * - Attempts to connect to WiFi by calling startNetwork().
 * - Starts the camera by calling startCamera().
 * - Starts the WebSocket server by calling startWebSocket().
 * - Starts the web server by calling startWebServer().
 */
void setup() {      
    Serial.begin(115200);      
    pinMode(LED_FLASHLIGHT, OUTPUT);  
    pinMode(CONTROL_PIN_FORWARD, OUTPUT);  
    pinMode(CONTROL_PIN_BACKWARD, OUTPUT);  
    pinMode(CONTROL_PIN_LEFT, OUTPUT);  
    pinMode(CONTROL_PIN_RIGHT, OUTPUT); 
      
    // Attempt to connect to WiFi      
    startNetwork();  
    
    // Start the camera      
    startCamera();      
    
    // Start WebSocket server    
    startWebSocket();    

    // Start Server
    startWebServer();
}      
  
void loop() {      
    // Handle WebSocket connections    
    webSocket.loop();    
  
    // Check for incoming WebSocket messages  
    String command = webSocketMessage();  
    if (command.length() > 0) {  
        handleMotorControl(command, true);  
    }  
      
    // Update motor states based on active commands  
    updateMotorStates();  

    // Send frames to WebSocket
    sendFrameToWebSocket();

}  
