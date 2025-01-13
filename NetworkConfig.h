#ifndef NETWORK_CONFIG_H  
#define NETWORK_CONFIG_H  
  
#include <WiFi.h>  
  
// Declare global variables as extern  
extern const char* wifiSSID;    
extern const char* wifiPassword;    
extern const int maxWiFiAttempts; // Max retry attempts for WiFi connection    
  
extern const char* ssid;  
extern const char* password;  
extern const IPAddress local_IP;  
extern const IPAddress gateway;  
extern const IPAddress subnet;  
  
void startNetwork();  
  
#endif // NETWORK_CONFIG_H  
