#include "WebSocketHandler.h"  
#include <esp_camera.h> // Include this for camera functions  
#include <Arduino.h>    // Include this for Serial functions  
  
WebSocketsServer webSocket = WebSocketsServer(81); // WebSocket server on port 81    
  
void startWebSocket() {  
    Serial.println("Starting Websocket");     
    webSocket.begin();    
    webSocket.onEvent(handleWebSocketMessage);    
}    
  
void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {    
    // Handle WebSocket messages if needed    
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
