#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Replace these with your WiFi credentials
const char* ssid = "techno";  //mention WiFi name
const char* password = "techno@123";  //mention WiFi password

// Define NTP Server address
const char* ntpServer = "in.pool.ntp.org";  //Modify as per your country
const long  gmtOffset_sec = 19800; // Offset from UTC (in seconds) (India GMT 5:30 // 5.5*60*60 = 19800) Modify as per your country
const int   daylightOffset_sec = 3600; // Daylight offset (in seconds)

// Define relay pin
const int relayPin = 33; // Change this to the pin connected to your relay

// Define OLED parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define NTP and WiFi objects
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

// Define variables for relay control
const int relayOnHour = 16;   // Relay ON time in 24HR
const int relayOnMinute = 0; // Relay ON time Minute
const int relayOffHour = 16;   // Relay OFF time in 24HR
const int relayOffMinute = 1; // Relay OFF time Minute
bool relayState = false;

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();
  delay(1000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  //uncomment for Active LOW relay
  //digitalWrite(relayPin, LOW);   //comment for Active LOW relay
  
  // Start NTP time sync
  timeClient.begin();
  timeClient.update();
}

void loop() {
  // Update NTP time
  timeClient.update();
  
  // Get current time
  time_t currentTime = timeClient.getEpochTime();
  struct tm * timeinfo;
  timeinfo = localtime(&currentTime);
  
  // Display current time on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Time: ");
  display.println(timeClient.getFormattedTime());
  display.println("--------------");
  display.print("On Time:  ");
  display.print(relayOnHour);
  display.print(":");
  display.println(relayOnMinute);
  display.print("Off Time: ");
  display.print(relayOffHour);
  display.print(":");
  display.println(relayOffMinute);
  display.display();
  
  // Check if it's time to toggle the relay
  if (timeinfo->tm_hour == relayOnHour && timeinfo->tm_min == relayOnMinute) {
    // Turn on the relay
    digitalWrite(relayPin, LOW); //uncomment for Active LOW relay
    //digitalWrite(relayPin, HIGH);  // comment for Active LOW relay
    relayState = true;
    Serial.println("Relay ON");
  } 
  else if (timeinfo->tm_hour == relayOffHour && timeinfo->tm_min == relayOffMinute){
    // Turn off the relay
    digitalWrite(relayPin, HIGH);  //uncomment for Active LOW relay
    //digitalWrite(relayPin, LOW);  // comment for Active LOW relay
    relayState = false;
    Serial.println("Relay OFF");
  }
  // Wait for 1 second before checking again
  delay(1000);
  
}
