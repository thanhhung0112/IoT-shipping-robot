String DataSend = "";
String DataSTM = "";
long last=0;

String hang="";
void read_ESP8266(void);
void send_Data(void);
void kiemtrahang(void);
#define hongngoai PB15
const int pwm1=PA1;
const int pwm2=PA2;
int i=15000;
int j=10000;
void setup()
{ 
  pinMode(pwm2,PWM);
  pinMode(pwm1,PWM);
  pinMode(hongngoai, INPUT);
  Serial1.begin(9600);
  
}
void loop()
{  /* if(millis()<5000){                                                                                                 
    pwmWrite(pwm1,i);
    pwmWrite(pwm2,i-j);
    digitalWrite(PA0,LOW);
    digitalWrite(PA3, LOW);
    i = i + 1000;
    delay(100);
    if (i>65535){
      i=65535;
      }
    j=j-1000;
    if (j<0){
      j=0;     
}
}
else {
    pwmWrite(pwm1,0);
    pwmWrite(pwm2,0);
  } 
*/
  read_ESP8266();
  kiemtrahang();
  if (millis()-last>=1500){
    send_Data();
    last=millis();
    }
    }
void kiemtrahang(void){
  if (digitalRead(hongngoai)==0){
    hang="1";
    }
  if (digitalRead(hongngoai)==1) {
    hang="0";
   }  
  }
void send_Data(void){
  Json(String(hang));
  }
void Json(String thamso1){
  DataSend="";
  DataSend= String(thamso1);
  Serial1.println(DataSend);
  Serial1.flush();
  }  
void read_ESP8266(void){
  while (Serial1.available()){
    char InChar = (char)Serial1.read();
    if (InChar != '\n'){
      DataSTM += InChar;
      }
    }
  }
