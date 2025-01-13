#include "NetworkConfig.h"  
  
// Define the global variables  
const char* wifiSSID = "ANDROID AP";    
const char* wifiPassword = "tes12345";    
const int maxWiFiAttempts = 20; // Max retry attempts for WiFi connection    
  
const char* ssid = "Hehe!";  
const char* password = "test12345";  
const IPAddress local_IP(192, 168, 1, 1);  
const IPAddress gateway(192, 168, 1, 1);  
const IPAddress subnet(255, 255, 255, 0);  
  
void startNetwork() {     
    // Attempt to connect to WiFi    
    WiFi.begin(wifiSSID, wifiPassword);    
    WiFi.setSleep(false);    
    Serial.print("Connecting to WiFi");  
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED && attempt < maxWiFiAttempts) { // Max attempts    
        delay(500);    
        Serial.print(".");    
        attempt++;    
    }    

    if (WiFi.status() == WL_CONNECTED) {      
        Serial.println("\nConnected to WiFi");      
        Serial.print("IP Address: ");      
        Serial.println(WiFi.localIP());      
    } else {  
        // Start SoftAP if WiFi fails  
        WiFi.softAPConfig(local_IP, gateway, subnet);  
        WiFi.softAP(ssid, password);  
        Serial.println("\nWiFi not found. Starting Access Point mode.");  
        Serial.print("AP IP Address: ");  
        Serial.println(WiFi.softAPIP());  
    }  
}  
