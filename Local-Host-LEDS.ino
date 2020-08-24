
// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
// Replace with your network credentials
const char* ssid     = "<put your wifi name here>";
const char* password = "<your wifi password here>";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state


// FastLED stuff
#define LED_PIN    D4
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() {

  Serial.begin(115200);

  //FastLEDS
  strip.begin();
  strip.show();
  strip.setBrightness(255);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /red") >= 0) {
              Serial.println("red is active");
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(255,   0,   0));
                strip.show();
              }
            } else if (header.indexOf("GET /green") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0,   255,   0));
                strip.show();
              }
            } else if (header.indexOf("GET /blue") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0,   0,   255));
                strip.show();
              }
            } else if (header.indexOf("GET /purple") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(160,   32,   420));
                strip.show();
              }
            } else if (header.indexOf("GET /magenta") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(255,   0,   255));
                strip.show();
              }
            } else if (header.indexOf("GET /yellow") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(255,   255,   0));
                strip.show();
              }
            } else if (header.indexOf("GET /white") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(255,   255,   255));
                strip.show();
              }
            } else if (header.indexOf("GET /Lblue") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0,   191,   25));
                strip.show();
              }
            } else if (header.indexOf("GET /lime") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(50,   205,   50));
                strip.show();
              }
            } else if (header.indexOf("GET /off") >= 0) {
              for (int i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0,   0,   0));
                strip.show();
              }
            } else if (header.indexOf("GET /rainbow") >= 0) {
              rainbow(10);
            }


            // Display the HTML web pssage
            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>LED remote control</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            // Web Page Heading
            client.println("<body><p><a href=\"/red\"><button class=\"but\" style=\"background-color: red;\">red</button></a></p>");
            client.println("<p><a href=\"/blue\"><button class=\"but\" style=\"background-color: blue;\">blue</button></a></p>");
            client.println("<p><a href=\"/green\"><button class=\"but\" style=\"background-color: green;\">green</button></a></p>");
            client.println("<p><a href=\"/magenta\"><button class=\"but\" style=\"background-color: magenta;\">magenta</button></a></p>");
            client.println(" <p><a href=\"/rainbow\"><button class=\"but\">rainbow</button></a></p>");
            client.println("<p><a href=\"/Lblue\"><button class=\"but\" style=\"background-color: skyblue;\">sky blue</button></a></p>");
            client.println("<p><a href=\"/lime\"><button class=\"but\" style=\"background-color: lime;\">lime</button></a></p>");
            client.println("<p><a href=\"/white\"><button class=\"but\" style=\"background-color: white;\">white</button></a></p>");
            client.println("<p><a href=\"/purple\"><button class=\"but\"  style=\"background-color: purple;\">purple</button></a></p>");
            client.println("<p><a href=\"/yellow\"><button class=\"but\" style=\"background-color: yellow;\">yellow</button></a></p>");
            client.println("<p><a href=\"/off\"><button class=\"but\">off</button></a></p>");
            client.println("<style>.but {height: 25px;}</style>");
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}


void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

