#ifndef WEBSOCKET_HANDLER_H  
#define WEBSOCKET_HANDLER_H  
  
#include <ESPAsyncWebServer.h>  
#include <WebSocketsServer.h>  
  
extern WebSocketsServer webSocket; // Declare it as extern  
  
void startWebSocket();  
void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t * payload, size_t length);  
void sendFrameToWebSocket();  
  
#endif // WEBSOCKET_HANDLER_H  
