#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

const char* ssid = "mySSID";
const char* password = "myPASSWORD";

//test change
void setup()
{
	Serial.begin(115200);

	while (Serial.available()) {}

	for (uint t = 4; t > 0; t--) {
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}
	WiFi.begin(ssid, password);
}

// Add the main program code into the continuous loop() function
void loop() {
	// wait for WiFi connection
	if ((WiFi.status() == WL_CONNECTED)) {

		t_httpUpdate_return ret = ESPhttpUpdate.update("http://10.34.4.187/ESP32_OTA.ino.esp32.bin");

		switch (ret) {
		case HTTP_UPDATE_FAILED:
			Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
			break;

		case HTTP_UPDATE_NO_UPDATES:
			Serial.println("HTTP_UPDATE_NO_UPDATES");
			break;

		case HTTP_UPDATE_OK:
			Serial.println("HTTP_UPDATE_OK");
			break;
		}
	}
}
