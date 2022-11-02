#define BLYNK_TEMPLATE_ID "TMPL5n82hPoz"
#define BLYNK_DEVICE_NAME "IoT"
#define BLYNK_AUTH_TOKEN "O9J5vnCH2nmyeP2lHs0bcKYCJq_QkNzZ"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
const byte RX = 14;
const byte TX = 12;
SoftwareSerial ESPSerial = SoftwareSerial(RX, TX);

char* auth = "O9J5vnCH2nmyeP2lHs0bcKYCJq_QkNzZ";

char* ssid = "Nguyen Hieu";
char* pass = "0359341471";

String DataESP = "";
String xuatphat="";
String DataSend;
long last;
void Read_STM(void);
void setup() {
  
  Serial.begin(9600);
  ESPSerial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  Read_STM();
  kiemtrahang();
  
  if (millis()-last>=1500){
    send_Data();
    last=millis();
    }
}
void kiemtrahang(void){
  if (DataESP=="1"){
    Serial.println("Co hang");
    Blynk.virtualWrite(V0, HIGH);
    }
  if (DataESP=="0") {
    Serial.println("Khong co hang");
    Blynk.virtualWrite(V0, LOW);
    }  
  }
void send_Data(void){
  Json(String(xuatphat));
  }
void Json(String thamso1){
  DataSend="";
  DataSend= String(thamso1);
  ESPSerial.println(DataSend);
  ESPSerial.flush();
  } 
void Read_STM(void){
  while (ESPSerial.available()){
    char InChar = (char)ESPSerial.read();
    if (InChar != '\n'){
      DataESP += InChar;
      }
    else {
      Serial.print("DataESP:");
      Serial.println(DataESP);
      DataESP="";
      }   
    }
  }
