#include <Arduino.h>  
#include "CameraConfig.h"  
#include "NetworkConfig.h"  
#include "WebSocketHandler.h" 
#include "WebServer.h" 
#include "GPIO.h"
  
void setup() {      
    Serial.begin(115200);      
    pinMode(LED_FLASHLIGHT, OUTPUT);  
      
    // Attempt to connect to WiFi      
    startNetwork();  
    
    // Start the camera      
    startCamera();      
    
    // Start WebSocket server    
    startWebSocket();    

    // Start Server
    startWebServer();
    
    pinMode(DYNAMO_PIN1, OUTPUT);
    pinMode(DYNAMO_PIN2, OUTPUT);

    pinMode(DYNAMO_PIN3, OUTPUT);
    pinMode(DYNAMO_PIN4, OUTPUT);
}      
  
int inputValue = 0;
void loop() {      
    // Handle WebSocket connections    
    webSocket.loop();    
    sendFrameToWebSocket(); // Send frames to WebSocket
}  
