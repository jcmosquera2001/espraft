# espraft

For those having issues with not detecting the device when plugged in.. **MAKE SURE YOUR USB CABLE IS FOR DATA, NOT ONLY CHARGING!** 

Installation for drivers only:

0. Ensure you have a DATA micro USB cable (typically one that came with a phone should work -- mine came with vapes and so only supported charging).
1. Try plugging in the board without installing drivers -- if you hear the connection sound for an external device you are good to go (skip to 3).
2. If you need drivers, SparkFun has them hosted (official wemos site seems to be down) -- I can't link to them but search google for "sparkfun CH340 drivers," and the first result should be "How to Install CH340 Drivers"
3. Verify you can see the device: open Device Manager --> Ports (COM & LPT) --> USB Serial CH340 (COMXYZ)

Getting setup in Arduino IDE:

0. You will need a link to copy and paste, but I can't link it here. Search Google for "arduino ide esp8266 board manager" -- the first result should be for a "readthedocs" website, and that should have all the instructions you need. However, for clarity I will list them here as well.
1. Ensure you have Python installed (this might be optional -- I haven't installed Python directly, but I installed the Arduino IDE and had no issues).
2. Open the Arduino IDE and go to File --> Preferences
3. Under "Additional Board Manager URLs" at the bottom, paste the link (it's to a JSON file) you copied from the other page into that box and hit "OK"
4. Go to Tools --> Board --> and select Board Manager (near the top)
5. Search for "ESP8266" and install the result (should be from "ESP8266 Community")

Selecting the board for your sketch:

1. Go to Tools --> Board and select either “LOLIN(WEMOS) D1 R2 & mini” or "NodeMCU 1.0 (12-E Module)" — either of these worked for me
2. Be sure to select which COM port the board from Tools -> Port
3. Check that the upload rate is 115200 (it should already be)

Test the board with "Blink":

1. Go to File --> Examples --> ESP8266 and select "Blink" at the top
2. You shouldn't need to change anything, so click Upload
3. Once it's finished, check that your blue led light is blinking

Test the board's WiFi with "ArduinoOTA":
0. This isn't necessary, but to be sure your WiFi module actually works you need to try connecting
1. Go to File --> Examples --> ArduinoOTA and select "BasicOTA"
2. Only changes you have to make are on lines 7 and 8 for your WiFi SSID and password
3. (Optional) Save the sketch
4. Go to Tools --> Port: If all was successful, you should be able to see the ESP8266 board here (COM whatever) -- select it
5. Hit upload and open the serial monitor
6. Once the program is finished uploading, make sure to change the baud rate to 115200 on the serial monitor
7. Check to make sure you get the "Ready" message, followed by an IP address
