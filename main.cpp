#include <WiFi.h>
// #include <FirebaseClient.h>
#include<Firebase_ESP_Client.h>

// WiFi credentials
#define WIFI_SSID "Anika"
#define WIFI_PASSWORD "Amirul#Anju23"

// Firebase settings
#define FIREBASE_HOST "https://esp32controller-3e341-default-rtdb.firebaseio.com/" // e.g., "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyB6nL4kCagETIzG9bbPIWAYuo-JxwN3Wv8" // You can get this from Firebase Console
#define gmail "toha@mail.com"
#define pass "toha1234"

unsigned long sendDataPrevMillis = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int pin=15;
//start 
void setup() {
  Serial.begin(115200);
  pinMode(pin, OUTPUT); // Use built-in LED pin

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize Firebase
  config.api_key=FIREBASE_AUTH;

  auth.user.email = gmail;
  auth.user.password = pass;
  config.database_url=FIREBASE_HOST;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
    // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;

}
void loop(){
if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    int ledState;
   if(Firebase.RTDB.getInt(&fbdo, "/led/status", &ledState)){
    digitalWrite(pin, ledState);
   }else{
    Serial.println(fbdo.errorReason().c_str());
   }
  }
}



