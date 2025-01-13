#include <ESPAsyncWebServer.h>  
#include <esp_camera.h> // Include this for camera functions  

#ifndef WEBSERVER_HANDLER
#define WEBSERVER_HANDLER  

extern AsyncWebServer webServer;
extern framesize_t currentFrameSize;

void startWebServer();
void handleHomepage(AsyncWebServerRequest *request);
void handleSetResolution(AsyncWebServerRequest *request);

#endif // WEBSERVER_HANDLER