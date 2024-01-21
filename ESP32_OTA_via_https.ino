#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

const char* ssid = "HezarFEN";
const char* password = "8BNQB5B8FDA";

void setup()
{
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();

	for (uint t = 4; t > 0; t--) {
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}
	WiFi.begin(ssid, password);
}
uint8_t connectionTryCount = 0;
// Add the main program code into the continuous loop() function
void loop() {
	// wait for WiFi connection
	while (WiFi.status() != WL_CONNECTED) {
		vTaskDelay(500 / portTICK_PERIOD_MS);
		Serial.print(".");
		if (connectionTryCount > 20)
		{
			connectionTryCount = 0;
			break;
		}
		else
		{
			connectionTryCount++;
		}
	}
	if ((WiFi.status() == WL_CONNECTED)) {
		//https://github.com/emretural/ESP32_OTA_via_https/releases/download/1.01/QuantumaQr.ino.bin
		//https://github.com/emretural/ESP32_OTA_via_https/releases/download/1.01/QuantumaQr.ino.bin
		//t_httpUpdate_return ret = ESPhttpUpdate.update("http://github.com/emretural/ESP32_OTA_via_https/releases/download/1.01/QuantumaQr.ino.bin", "", "21 99 13 84 63 72 17 13 B9 ED 0E 8F 00 A5 9B 73 0D D0 56 58");
		//t_httpUpdate_return ret = ESPhttpUpdate.update("https://raw.githubusercontent.com/Zyxmn/esp8266_BlinkyBin/master/Blinky.cpp.bin", "", "21 99 13 84 63 72 17 13 B9 ED 0E 8F 00 A5 9B 73 0D D0 56 58");
		//t_httpUpdate_return ret = ESPhttpUpdate.update("https://github.com/emretural/ESP32_OTA_via_https/releases/download/1.01/QuantumaQr.ino.bin","", "C7 07 27 78 85 F2 9D 33 C9 4C 5E 56 7D 5C D6 8E 72 67 EB DE");
		t_httpUpdate_return ret = ESPhttpUpdate.update("http://device.actiontime.us/QuantumaQr.ino.bin");

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
