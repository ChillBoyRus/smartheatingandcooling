

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

const char* ssid = "IT";
const char* password = "kvantorium";


const char* serverName = "http://davideqc.beget.tech/heater/index.php?id=1";
String serverNametwo = "http://davideqc.beget.tech/heater/setrealtemp.php?id=1&realtemp=";

unsigned long lastTime = 0;


unsigned long timerDelay = 5000;

String sensorReadings;
int sensorReadingsArr[1];

void setup() {
  Serial.begin(115200);
#include <math.h>
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);
pinMode(D8, OUTPUT);
pinMode(A0, INPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {

 
  if ((millis() - lastTime) > timerDelay) {
      
      float voltage = analogRead(A0)*5.0/1023.0;
      Serial.println("Voltage "+(String)voltage);
      float temperature = 1.0 / (log(voltage /2.5) / 4300 + 1.0/ 298.0) -273.0;
      
       Serial.println(temperature);
  
      if(WiFi.status()== WL_CONNECTED){
      sensorReadings = httpGETRequest(serverName);
      httpGETRequest((serverNametwo+(int)temperature).c_str());
      Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);
  
      
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
    
      JSONVar keys = myObject.keys();
    
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.println(value);
    
      }
      Serial.println(myObject["temp"]);
      Serial.println("sensor ");
      Serial.print(temperature);
        Serial.print("server ");
        int settedtemp = (String((const char*) myObject["temp"])).toInt();
        int facticmode = (String((const char*) myObject["facticmode"])).toInt();
      Serial.print("Mode " + facticmode);
      if(facticmode == 0){
        if(settedtemp < temperature){
        Serial.println("chilling");
        digitalWrite(D5, LOW);
        digitalWrite(D6, HIGH);
        digitalWrite(D7, LOW);
        digitalWrite(D8, HIGH);
      }else
      {
        digitalWrite(D5, HIGH);
        digitalWrite(D6, LOW);
        digitalWrite(D7, HIGH);
        digitalWrite(D8, LOW);
        Serial.println("heating");
      }
      }else if (facticmode == 1){
        digitalWrite(D5, HIGH);
        digitalWrite(D6, LOW);
        digitalWrite(D7, HIGH);
        digitalWrite(D8, LOW);
        Serial.println("heating");
      }else{
        Serial.println("chilling");
        digitalWrite(D5, LOW);
        digitalWrite(D6, HIGH);
        digitalWrite(D7, LOW);
        digitalWrite(D8, HIGH);
      }

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
