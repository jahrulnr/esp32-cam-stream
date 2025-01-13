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
  
/**
 * @brief Starts the network connection process.
 * 
 * This function attempts to connect to a WiFi network using the provided 
 * SSID and password. If the connection is successful, it prints the IP 
 * address assigned to the device. If the connection fails after a 
 * specified number of attempts, it starts the device in Access Point (AP) 
 * mode with a predefined SSID and password, and prints the AP IP address.
 * 
 * @note Ensure that the WiFi credentials (wifiSSID and wifiPassword) and 
 * the AP configuration (local_IP, gateway, subnet, ssid, password) are 
 * correctly defined before calling this function.
 */
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
