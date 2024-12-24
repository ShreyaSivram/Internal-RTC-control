# Internal-RTC-control
This code demonstrates connecting an ESP32 to a WiFi network and an NTP (Network Time Protocol) server to display accurate time on an OLED screen and control a relay based on specific times. Key features include:

- WiFi Connection: Connects to a specified WiFi network.
- NTP Time Sync: Retrieves current time from an NTP server.
- OLED Display: Shows real-time clock and relay schedule using the Adafruit_SSD1306 library.
- Relay Control: Toggles a relay on and off at predetermined times via GPIO pins.

This setup is ideal for automated tasks requiring accurate, synchronized timekeeping and display.
Make the necessary connections.
Make sure all the components like the ESP32, relay and the OLED are connected to a supply. Now compile and upload the code into the ESP32 board.
After uploading the code, the OLED initializes and connects to the NTP server.
After which, the internal RTC of the ESP32 takes care of the time.
Now, the relay makes sure that the LED switches on only during the ON time and switches back off at the OFF time.




