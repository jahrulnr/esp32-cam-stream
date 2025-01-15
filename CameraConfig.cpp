#include "CameraConfig.h"  
#include <esp_camera.h> // Include this for camera functions  
#include <Arduino.h>    // Include this for Serial functions  
  
sensor_t *s;  
framesize_t currentFrameSize = FRAMESIZE_QVGA; // Default frame size    
  
/**
 * @brief Initializes and starts the camera with the specified configuration.
 * 
 * This function sets up the camera configuration parameters, including pin assignments,
 * clock frequency, pixel format, frame size, and buffer location. It also checks for the
 * presence of PSRAM and adjusts the configuration accordingly. Finally, it initializes
 * the camera and prints an error message if the initialization fails.
 * 
 * @note The function assumes that the necessary GPIO pin definitions (e.g., Y2_GPIO_NUM, 
 * XCLK_GPIO_NUM) and camera configuration structures (e.g., camera_config_t) are defined 
 * elsewhere in the code.
 * 
 * @return void
 */
void startCamera() {   
    Serial.println("Starting Camera");   
    camera_config_t config;    
    config.ledc_channel = LEDC_CHANNEL_0;    
    config.ledc_timer = LEDC_TIMER_0;    
    config.pin_d0 = Y2_GPIO_NUM;    
    config.pin_d1 = Y3_GPIO_NUM;    
    config.pin_d2 = Y4_GPIO_NUM;    
    config.pin_d3 = Y5_GPIO_NUM;    
    config.pin_d4 = Y6_GPIO_NUM;    
    config.pin_d5 = Y7_GPIO_NUM;    
    config.pin_d6 = Y8_GPIO_NUM;    
    config.pin_d7 = Y9_GPIO_NUM;    
    config.pin_xclk = XCLK_GPIO_NUM;    
    config.pin_pclk = PCLK_GPIO_NUM;    
    config.pin_vsync = VSYNC_GPIO_NUM;    
    config.pin_href = HREF_GPIO_NUM;    
    config.pin_sscb_sda = SIOD_GPIO_NUM;    
    config.pin_sscb_scl = SIOC_GPIO_NUM;    
    config.pin_pwdn = PWDN_GPIO_NUM;    
    config.pin_reset = RESET_GPIO_NUM;    
    config.xclk_freq_hz = 16 * 1000000; // 16Hz    
    config.pixel_format = PIXFORMAT_JPEG;    
    config.frame_size = FRAMESIZE_QVGA; // Set default frame size    
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;    
    config.fb_location = CAMERA_FB_IN_PSRAM;    
  
    if (psramFound()) {    
        config.jpeg_quality = 12;    
        config.fb_count = 1;    
        config.grab_mode = CAMERA_GRAB_LATEST;    
    } else {    
        // Limit the frame size when PSRAM is not available    
        config.frame_size = FRAMESIZE_SVGA;    
        config.fb_location = CAMERA_FB_IN_DRAM;    
        config.jpeg_quality = 12;    
        config.fb_count = 1;    
    }    
  
    // Initialize the camera      
    esp_err_t err = esp_camera_init(&config);      
    if (err != ESP_OK) {      
        Serial.printf("Camera init failed with error 0x%x", err);      
        return;      
    }      
  
    s = esp_camera_sensor_get();  
}  
