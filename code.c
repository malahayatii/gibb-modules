#include <WiFiUdp.h> 
#include <WiFiServer.h> 
#include <WiFi.h> 
#include <WiFiSTA.h> 
#include <WiFiScan.h> 
#include <WiFiType.h> 
#include <WiFiMulti.h> 
#include <WiFiGeneric.h> 
#include <WiFiClient.h> 

#define SensorPin 21 

#include <HTTPClient.h> 

  

const char* ssid = "Secs10s"; 

const char* password = "kvct8227"; 

  

// This is the server address endpoint 

const char* serverAddress = "https://arduino.kubelize.com/trigger"; 

  

void setup() { 

  Serial.begin(115200); 

  pinMode(SensorPin, INPUT); 

  Serial.begin(9600); 

   

  // Connect to Wi-Fi 

  WiFi.begin(ssid, password); 

  Serial.print("Connecting to "); 

  Serial.println(ssid); 

  

  while (WiFi.status() != WL_CONNECTED) { 

    delay(1000); 

    Serial.print("."); 

  } 

  Serial.println(""); 

  Serial.println("WiFi connected"); 

} 

  

void loop() { 

  // Check the sensor condition 

  if (digitalRead(SensorPin) != 0) { 

    Serial.println("Sensor condition fulfilled"); 

  

    // Create an HTTP object 

    HTTPClient http; 

  

    // Your POST data 

    String postData = "sensor_triggered"; 

  

    // Start HTTP connection 

    http.begin(serverAddress); 

  

    // Add headers 

    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 

  

    // Send POST request 

    int httpResponseCode = http.POST(postData); 

  

    // Check for successful response 

    if (httpResponseCode > 0) { 

      Serial.print("HTTP Response code: "); 

      Serial.println(httpResponseCode); 

      String payload = http.getString(); // Get response payload 

      Serial.println(payload); // Print response payload 

    } else { 

      Serial.print("Error code: "); 

      Serial.println(httpResponseCode); 

    } 

  

    // End HTTP connection 

    http.end(); 

  } 

  

  // Wait for some time before checking the sensor condition again 

  delay(5000); 

} 