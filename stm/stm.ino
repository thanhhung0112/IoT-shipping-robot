#include <ArduinoJson.h>

String S;
String D;

float arr1[9] = {4000, 2000, 4000, 500, 4000, 1700, 3000, 1000, 500};
int state = -1;
String DataSend = "";
String DataSTM = "";
long last = 0;
long lastT = 0;
long lastP = 0;
long last0 = 0;
long lastC = 0;
long vT;
int vTrai = 0;
int pwmT = 40000;
long T = 0;
long T1 = 0;
long vP;
int vPhai = 0;
int pwmP = 41250;
long P = 0;
long P1 = 0;
bool rt = 0;
bool rp = 0;

String xuatphat;
String hang = "";
String vatcan = "";
void read_ESP8266(void);
void send_Data(void);
void kiemtrahang(void);
void kiemtravatcan(void);
void chondiemden(void);


#define hongngoai PA15
#define trig PB8
#define echo PB7
#define ecdT PA6
#define ecdP PA4



int khoangcach;
const int pwm1 = PA0;
const int pwm2 = PA3;
int i = 0;
int j = 0;

void setup()
{
  pinMode(ecdT, INPUT_PULLUP);
  pinMode(ecdP, INPUT_PULLUP);
  pinMode(PA1, OUTPUT);
  pinMode(PA2, OUTPUT);
  pinMode(pwm2, PWM);
  pinMode(pwm1, PWM);
  pinMode(hongngoai, INPUT_PULLUP);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial1.begin(19200);
  Serial.begin(9600);
}

void loop()
{
  read_ESP8266();
  chondiemden();
  if (rt == 1) {
    pwmWrite(pwm1, 0);
    digitalWrite(PA1, LOW);
    pwmWrite(pwm2, pwmP);
    digitalWrite(PA2, LOW);
    delay(850);
    rt = 0;
    state++;
    last0 = millis();
  }
  else if (rp == 1) {
    pwmWrite(pwm1, pwmT);
    digitalWrite(PA1, LOW);
    pwmWrite(pwm2, 0);
    digitalWrite(PA2, LOW);
    delay(850);
    rp = 0;
    state++;
    last0 = millis();
  }
  while (state == -1) {
    pwmWrite(pwm1, 0);
    digitalWrite(PA1, LOW);
    pwmWrite(pwm2, 0 );
    digitalWrite(PA2, LOW);
    kiemtrahang();
    kiemtravatcan();
    /*Serial.print("state:");
    Serial.println(state);*/
    if (millis() - last >= 500) {
      send_Data();
      last = millis();
    }
    read_ESP8266();
    if (xuatphat == "1") state = 0;
    last0 = millis();
  }
  if ((rt == 0) && (rp == 0) && (state < 9)) {
    pwmWrite(pwm1, pwmT);
    digitalWrite(PA1, LOW);
    pwmWrite(pwm2, pwmP);
    digitalWrite(PA2, LOW);
    kiemtravatcan();
    lastC = millis();
    while (khoangcach <= 20) {
      pwmWrite(pwm1, 0);
      pwmWrite(pwm2, 0);
      kiemtrahang();
      kiemtravatcan();
      if (millis() - last >= 500) {
        send_Data();
        last = millis();
      }

    }
    
    last0 = last0 + (millis() - lastC);
    
    
  }
  if (abs(millis() - last0 - arr1[state]) <= 10) {
    if (state == 0) rt = 1;
    else if (state == 1) rt = 1;
    else if (state == 2) rt = 1;
    else if (state == 3) rt = 1;
    else if (state == 4) rp = 1;
    else if (state == 5) rp = 1;
    else if (state == 6) {
      while (digitalRead(hongngoai) == 0) {
        pwmWrite(pwm1, 0);
        digitalWrite(PA1, LOW);
        pwmWrite(pwm2, 0);
        digitalWrite(PA2, LOW);
        kiemtrahang();
        kiemtravatcan();
        if (millis() - last >= 500) {
          send_Data();
          last = millis();
        }
      }
      state++;
      last0 = millis();
    }
    else if (state == 7) rt = 1;
    else if (state == 8) rt = 1;
  }
  if (state == 9) {
    pwmWrite(pwm1, 0);
    pwmWrite(pwm2, 0);
  }
  kiemtrahang();
  kiemtravatcan();
  /*Serial.print("state:");
  Serial.println(state);  
  Serial.println(abs(millis() - last0));
  Serial.print("lastC:");
  Serial.println(lastC);
  Serial.println(millis() - lastC);*/
  if (millis() - last >= 500) {
    send_Data();
    last = millis();
  }
}
void chondiemden(void) {
  if (S = "S1") {arr1[6]=4000; arr1[7]=1000;}
  else if (S = "S2") {arr1[6]=4000; arr1[7]=1000;}
  else if (S = "S3") {arr1[6]=4000; arr1[7]=1000;}
  else if (S = "S4") {arr1[6]=4000; arr1[7]=1000;}
  if (D = "DA") {arr1[2]=4000; arr1[4]=1000;}
  else if (D = "DA") {arr1[2]=4000; arr1[4]=1000;}
  else if (D = "DA") {arr1[2]=4000; arr1[4]=1000;}
}
void kiemtrahang(void) {
  if (digitalRead(hongngoai) == 0) {
    hang = "1";
  }
  if (digitalRead(hongngoai) == 1) {
    hang = "0";
  }
}

void kiemtravatcan(void) {
  unsigned long duration;
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(5);
  digitalWrite(trig, 0);
  duration = pulseIn(echo, HIGH);
  khoangcach = int((duration / 2) / 29.412);
  if (khoangcach <= 20) {
    vatcan = "1";
  }
  else {
    vatcan = "0";
  }

}
void send_Data(void) {
  Json(String(hang), String(vatcan));
}

void Json(String thamso1, String thamso2) {
  DataSend = "";
  DataSend = "{\"hang\":\"" + thamso1 + "\"," +
             "\"vatcan\":\"" + thamso2 + "\"}";
  Serial1.println(DataSend);
  Serial.println(DataSend);
  Serial1.flush();
}

void read_ESP8266(void) {
  while (Serial1.available()) {
    char InChar = (char)Serial1.read();
    if (InChar != '\n') {
      DataSTM += InChar;
    }
    else {
      Serial.print("DataSTM:");
      Serial.println(DataSTM);
      XuliJson(DataSTM);
      Serial.println("---------------");
      DataSTM = "";
    }
  }
}

void XuliJson(String DataSTM) {
  const size_t capacity = JSON_OBJECT_SIZE(2) + 256;
  DynamicJsonDocument JSON(capacity);
  deserializeJson(JSON, DataSTM);

  if (JSON["xuatphat"] == "0") {
    xuatphat = "0";
  }
  if (JSON["xuatphat"] == "1") {
    xuatphat = "1";
  }
  if (JSON["S"] == "S1") {
    S = "S1";
  }
  if (JSON["S"] == "S2") {
    S = "S2";
  }
  if (JSON["S"] == "S3") {
    S = "S3";
  }
  if (JSON["S"] == "S4") {
    S = "S4";
  }
  if (JSON["S"] == "S4") {
    S = "S4";
  }
  if (JSON["D"] == "DA") {
    D = "DA";
  }
  if (JSON["D"] == "DB") {
    D = "DB";
  }
  if (JSON["D"] == "DC") {
    D = "DC";
  }

  Serial.print("xuatphat:"); Serial.println(xuatphat);
  Serial.print("S:"); Serial.println(S);
  Serial.print("D:"); Serial.println(D);
}
