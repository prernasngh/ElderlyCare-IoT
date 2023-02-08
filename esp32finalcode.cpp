#include <SoftwareSerial.h>
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "piyush"
#define WIFI_PASSWORD "piyush01"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyAx2yCUf8X14sXTUiyfxbCXesN66EaOkAs"

/* 3. Define the RTDB URL */
#define DATABASE_URL "it07-966b9-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

SoftwareSerial espSerial(3,1); // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  while (!espSerial) {;}
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
      config.api_key = API_KEY;

    config.database_url = DATABASE_URL;

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
    // otherwise the SSL connection will fail.
    //////////////////////////////////////////////////////////////////////////////////////////////

    Firebase.begin(DATABASE_URL, API_KEY);
}

void loop() {
  if (espSerial.available()) {
    // String receivedData = espSerial.readString();
    // if (receivedData.length() > 0) {
    //   Serial.println("Data received: " + receivedData);
    int data=espSerial.read();
    Serial.println(data);
      if (Firebase.ready())
    {

        // //Firebase.setInt(fbdo, main, 5);
        // Firebase.setString(fbdo, "/test/a", buffer);
        Firebase.setInt(fbdo, "/test/a", data);
    }
    }

  delay(1000);
}
