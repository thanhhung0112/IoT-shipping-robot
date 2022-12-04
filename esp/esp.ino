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
String hang = "";
String vatcan = "";
String xuatphat;
String state;
String S;
String D;
String DataSend;
long last;
void Read_STM(void);

int buttonV1;


void setup() {
  Serial.begin(9600);
  ESPSerial.begin(19200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  Read_STM();

  /*if (millis()-last>=1500){
    send_Data();
    last=millis();
    }*/
}
BLYNK_CONNECTED() {
  Blynk.syncAll();
}
BLYNK_WRITE(V1) {
  int buttonV1 = param.asInt();
  if (buttonV1 == 0) {
    xuatphat = "0";
  }
  else {
    xuatphat = "1";
  }
}
BLYNK_WRITE(V12) {
  int buttonV12 = param.asInt();
  if (buttonV12 == 1) {
    S = "S1";
    Blynk.virtualWrite(V13, LOW);
    Blynk.virtualWrite(V14, LOW);
    Blynk.virtualWrite(V15, LOW);
  }
}
BLYNK_WRITE(V13) {
  int buttonV13 = param.asInt();
  if (buttonV13 == 1) {
    S = "S2";
    Blynk.virtualWrite(V12, LOW);
    Blynk.virtualWrite(V14, LOW);
    Blynk.virtualWrite(V15, LOW);
  }
}
BLYNK_WRITE(V14) {
  int buttonV14 = param.asInt();
  if (buttonV14 == 1) {
    S = "S3";
    Blynk.virtualWrite(V13, LOW);
    Blynk.virtualWrite(V12, LOW);
    Blynk.virtualWrite(V15, LOW);
  }
}
BLYNK_WRITE(V15) {
  int buttonV15 = param.asInt();
  if (buttonV15 == 1) {
    S = "S4";
    Blynk.virtualWrite(V13, LOW);
    Blynk.virtualWrite(V14, LOW);
    Blynk.virtualWrite(V12, LOW);
  }
}
BLYNK_WRITE(V16) {
  int buttonV16 = param.asInt();
  if (buttonV16 == 1) {
    D = "DA";
    Blynk.virtualWrite(V17, LOW);
    Blynk.virtualWrite(V18, LOW);
  }
}
BLYNK_WRITE(V17) {
  int buttonV17 = param.asInt();
  if (buttonV17 == 1) {
    D = "DB";
    Blynk.virtualWrite(V16, LOW);
    Blynk.virtualWrite(V18, LOW);
  }
}
BLYNK_WRITE(V18) {
  int buttonV18 = param.asInt();
  if (buttonV18 == 1) {
    D = "DC";
    Blynk.virtualWrite(V16, LOW);
    Blynk.virtualWrite(V17, LOW);
  }
}
void kiemtrahang(void) {
  if (hang == "1") {
    Serial.println("Co hang");
    Blynk.virtualWrite(V0, HIGH);
  }
  if (hang == "0") {
    Serial.println("Khong co hang");
    Blynk.virtualWrite(V0, LOW);
  }
}
void kiemtravatcan(void) {
  if (vatcan == "1") {
    Serial.println("Co vat can");
    Blynk.virtualWrite(V11, HIGH);
  }
  if (vatcan == "0") {
    Serial.println("Khong co vat can");
    Blynk.virtualWrite(V11, LOW);
  }
}
void send_Data(void) {
  Json(String(xuatphat) , String(S) , String(D));
}
void Json(String thamso1, String thamso2, String thamso3 ) {
  DataSend = "";
  DataSend = "{\"xuatphat\":\"" + thamso1 + "\"," +
             "\"S\":\"" + thamso2 + "\"," +
             "\"D\":\"" + thamso3 + "\"}";
  ESPSerial.println(DataSend);
  ESPSerial.flush();
}
void Read_STM(void) {
  while (ESPSerial.available()) {
    char InChar = (char)ESPSerial.read();
    if (InChar != '\n') {
      DataESP += InChar;
    }
    else {
      Serial.print("DataESP:");
      Serial.println(DataESP);
      XuliJson(DataESP);
      kiemtrahang();
      kiemtravatcan();
      Serial.println("---------------");
      DataESP = "";
      delay(5);
      send_Data();
    }
  }
}
void XuliJson(String DataESP) {
  const size_t capacity = JSON_OBJECT_SIZE(2) + 256;
  DynamicJsonDocument JSON(capacity);
  deserializeJson(JSON, DataESP);

  if (JSON["hang"] == "0") {
    hang = "0";
  }
  if (JSON["hang"] == "1") {
    hang = "1";
  }
  if (JSON["vatcan"] == "0") {
    vatcan = "0";   
  }
  if (JSON["vatcan"] == "1") {
    vatcan = "1";
  }

  Serial.print("hang:"); Serial.println(hang);
  Serial.print("vatcan:"); Serial.println(vatcan);

}
