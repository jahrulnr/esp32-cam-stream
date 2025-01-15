#include "WebSocketHandler.h"  
#include <esp_camera.h> // Include this for camera functions  
#include <Arduino.h>    // Include this for Serial functions  
  
WebSocketsServer webSocket = WebSocketsServer(81); // WebSocket server on port 81 
String lastMessage; // Global variable to store the last received message     
  
void startWebSocket() {  
    Serial.println("Starting Websocket");     
    webSocket.begin();    
    webSocket.onEvent(handleWebSocketMessage);    
}    

String webSocketMessage() {
    return lastMessage; // Return the last received message  
}
  
void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {     
    if (type == WStype_TEXT) { // Check if the message is of type text  
        lastMessage = String((char*)payload); // Store the received message  
        Serial.printf("Received message: %s\n", lastMessage.c_str()); // Print the message to the serial monitor  
    }     
}    
  
/**
 * @brief Sends a frame captured from the camera to all connected WebSocket clients.
 * 
 * This function captures a frame from the ESP32 camera and broadcasts it to all
 * connected WebSocket clients using binary data. If the frame buffer cannot be
 * retrieved, an error message is printed to the serial monitor.
 * 
 * @note Ensure that the WebSocket server is properly initialized and that clients
 *       are connected before calling this function.
 */
void sendFrameToWebSocket() {    
    camera_fb_t *fb = esp_camera_fb_get(); // Get a frame from the camera    
    if (!fb) {    
        Serial.println("Failed to retrieve frame buffer!");    
        return;    
    }    
  
    // Send the frame over WebSocket    
    webSocket.broadcastBIN(fb->buf, fb->len);    
    esp_camera_fb_return(fb); // Return the frame buffer    
}  
