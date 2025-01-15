#include "WebServer.h"  

AsyncWebServer webServer(80);   
// framesize_t currentFrameSize = FRAMESIZE_QVGA;

void startWebServer() {
    Serial.println("Starting WebServer");   
    webServer.on("/", HTTP_GET, handleHomepage);
  
    // Endpoint to handle resolution change  
    webServer.on("/set_resolution", HTTP_GET, handleSetResolution);  
  
    // Start the server    
    webServer.begin();  

}

/**
 * @brief Handles the homepage request and serves the HTML page.
 * 
 * This function responds to the request for the homepage by sending an HTML page that
 * displays a live stream from the ESP32-CAM. The HTML page includes controls for adjusting
 * the brightness, saturation, and contrast of the video stream, as well as buttons to switch
 * the camera resolution. The video stream is displayed using a WebSocket connection.
 * 
 * @param request Pointer to the AsyncWebServerRequest object that contains information about the request.
 */
void handleHomepage(AsyncWebServerRequest *request) {
    // Serve the HTML page  
    request->send(200, "text/html", R"rawliteral(          
    <!DOCTYPE html>          
    <html>          
    <head>          
        <title>ESP32-CAM WebSocket Stream</title>          
        <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">  
        <style>          
            body { margin: 0; padding: 0; overflow: hidden; }          
            input { display: block; }          
            img {           
                width: 100vw;           
                height: 100vh;           
                object-fit: contain;           
                transform: rotate(180deg) scaleX(1);          
            }          
            .top-menu {          
                position: fixed;          
                top: 10px;          
                left: 10px;            
                right: 10px;  
                display: flex;          
                gap: 10px;          
                overflow: auto;  
                width: 100%;  
            }          
            .bottom-menu {          
                position: fixed;          
                bottom: 10px;          
                left: 10px;            
                right: 10px;  
                display: flex;          
                gap: 10px;        
                width: 100%;  
            }           
            .over-x {  
              overflow-x: auto !important;  
              white-space: nowrap;  
            }  
            .container {          
                padding: 10px 20px;          
                font-size: 16px;          
                border: none;          
                border-radius: 5px;          
                background-color: rgba(0, 0, 0, 0.5);          
                color: white;          
                cursor: pointer;          
            }          
            .remote-control {          
                display: flex;  
                position: fixed;          
                bottom: 80px;          
                left: 10px;          
                right: 10px;  
                justify-content: space-between;  
            }          
            .direction-buttons {          
                display: flex;          
                flex-direction: row;          
                justify-content: center;          
                gap: 10px;          
            }          
            .vertical-buttons {          
                display: flex;          
                flex-direction: column;          
                gap: 10px;          
            }         
        </style>          
    </head>          
    <body>           
        <img id="cameraStream" src="" alt="Camera Stream" loading="eager" fetchpriority="high"/>          
        <div class="top-menu">          
            <div class="container">          
                Brightness          
                <input id="brightness" value="0" min="0" max="100" oninput="changeFilter()" onmousemove="changeFilter()" ontouchmove="changeFilter()" type="range">          
            </div>          
            <div class="container">          
                Saturate          
                <input id="saturate" value="0" min="0" max="100" oninput="changeFilter()" onmousemove="changeFilter()" ontouchmove="changeFilter()" type="range">          
            </div>          
            <div class="container">          
                Contrast          
                <input id="contrast" value="0" min="0" max="100" oninput="changeFilter()" onmousemove="changeFilter()" ontouchmove="changeFilter()" type="range">          
            </div>          
        </div>           
        <div class="bottom-menu">  
          <div class="over-x">      
            <span class="container" id="fps">0 FPS</span>           
            <button class="container" onclick="switchCamSize('240x240')">240x240</button>          
            <button class="container" onclick="switchCamSize('QVGA')">QVGA</button>          
            <button class="container" onclick="switchCamSize('HVGA')">HVGA</button>          
            <button class="container" onclick="switchCamSize('VGA')">VGA</button>          
            <button class="container" onclick="switchCamSize('SVGA')">SVGA</button>          
            <button class="container" onclick="switchCamSize('XGA')">XGA</button>          
            <button class="container" onclick="switchCamSize('HD')">HD</button>          
            <button class="container" onclick="switchCamSize('SXGA')">SXGA</button>      
            <button class="container" onmousedown="sendCommand('stopA');sendCommand('stopB')" ontouchstart="sendCommand('stopA');sendCommand('stopB')">Stop</button>    
          </div>  
        </div>          
            
        <div class="remote-control">          
            <div class="vertical-buttons">          
                <button class="container" ontouchstart="sendCommand('forward')" ontouchend="sendCommand('stopA')">Forward</button>          
                <button class="container" ontouchstart="sendCommand('backward')" ontouchend="sendCommand('stopA')">Backward</button>          
            </div>          
            <div class="direction-buttons">          
                <button class="container" ontouchstart="sendCommand('left')" ontouchend="sendCommand('stopB')">Left</button>          
                <button class="container" ontouchstart="sendCommand('right')" ontouchend="sendCommand('stopB')">Right</button>          
            </div>               
        </div>      
        
        <script>          
            let countFrame = 0;      
            var ws = new WebSocket('ws://' + window.location.hostname + ':81/');          
            ws.binaryType = 'blob'; // Set binary type to blob          
            ws.onmessage = function(event) {          
                var img = document.getElementById('cameraStream');          
                img.src = URL.createObjectURL(event.data);          
                countFrame++;      
            };          
            var filters = {          
                brightness: 0,          
                saturate: 0,          
                contrast: 0,          
            };          
            let img = document.querySelector("img");          
            const changeFilter = function() {          
                const brightness = document.querySelector("#brightness");          
                const saturate = document.querySelector("#saturate");          
                const contrast = document.querySelector("#contrast");          
                filters.brightness = brightness.value;          
                filters.saturate = saturate.value;          
                filters.contrast = contrast.value;          
                const count_brightness = filters.brightness / 100 + 1;          
                const count_saturate = filters.saturate / 50 + 1;          
                const count_contrast = filters.contrast / 100 + 1;          
                img.style.filter = `brightness(${count_brightness}) saturate(${count_saturate}) contrast(${count_contrast})`;          
            };          
    
            function switchCamSize(size) {          
                fetch('/set_resolution?size=' + size) // Send request to change resolution        
                    .then(response => {        
                        if (response.ok) {        
                            console.log('Resolution changed to ' + size);        
                        } else {        
                            console.error('Failed to change resolution');        
                        }        
                    });        
            }          
    
            function sendCommand(command) {      
                if (ws.readyState === WebSocket.OPEN) {      
                    ws.send(command);      
                    console.log('Sent command: ', command);      
                } else {      
                    console.error('WebSocket is not open. Unable to send command.');      
                }      
            }      
    
            // Keyboard controls  
            window.addEventListener('keydown', function(event) {  
                switch(event.key) {  
                    case 'w':  
                    case 'ArrowUp':  
                        sendCommand('forward');  
                        break;  
                    case 's':  
                    case 'ArrowDown':  
                        sendCommand('backward');  
                        break;  
                    case 'a':  
                    case 'ArrowLeft':  
                        sendCommand('left');  
                        break;  
                    case 'd':  
                    case 'ArrowRight':  
                        sendCommand('right');  
                        break;  
                }  
            });  
  
            window.addEventListener('keyup', function(event) {  
                switch(event.key) {  
                    case 'w':  
                    case 'ArrowUp':  
                    case 's':  
                    case 'ArrowDown':  
                        sendCommand('stopA');  
                        break;  
                    case 'a':  
                    case 'ArrowLeft':  
                    case 'd':  
                    case 'ArrowRight':  
                        sendCommand('stopB');  
                        break;  
                }  
            });  
  
            setInterval(function(){      
                document.querySelector('#fps').innerHTML = countFrame + " FPS";      
                countFrame = 0;      
            }, 1000);      
        </script>          
    </body>          
    </html>          
)rawliteral");    
 


}

void handleSetResolution(AsyncWebServerRequest *request) {  
    if (request->hasParam("size")) {  
        String sizeValue = request->getParam("size")->value();  
        if (sizeValue == "240x240") {  
            currentFrameSize = FRAMESIZE_240X240;  
        } else if (sizeValue == "QVGA") {  
            currentFrameSize = FRAMESIZE_QVGA;  
        } else if (sizeValue == "HVGA") {  
            currentFrameSize = FRAMESIZE_HVGA;  
        } else if (sizeValue == "VGA") {  
            currentFrameSize = FRAMESIZE_VGA;  
        } else if (sizeValue == "SVGA") {  
            currentFrameSize = FRAMESIZE_SVGA;  
        } else if (sizeValue == "XGA") {  
            currentFrameSize = FRAMESIZE_XGA;  
        } else if (sizeValue == "HD") {  
            currentFrameSize = FRAMESIZE_HD;  
        } else if (sizeValue == "SXGA") {  
            currentFrameSize = FRAMESIZE_SXGA;  
        } else {  
            request->send(400, "text/plain", "Invalid resolution");  
            return;  
        }  
  
        // Update the camera frame size  
        sensor_t *s = esp_camera_sensor_get();  
        s->set_framesize(s, currentFrameSize);  
        request->send(200, "text/plain", "Resolution set to " + sizeValue);  
    } else {  
        request->send(400, "text/plain", "Bad Request");  
    }  
}  