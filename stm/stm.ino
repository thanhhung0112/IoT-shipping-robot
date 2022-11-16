String DataSend = "";
String DataSTM = "";
long last=0;

String hang="";
String vatcan="";
void read_ESP8266(void);
void send_Data(void);
void kiemtrahang(void);
void kiemtravatcan(void);

#define hongngoai PA15
#define trig PB8
#define echo PB9

int khoangcach;
const int pwm1=PA1;
const int pwm2=PA2;
int i=65535;
int j=30000;

void setup()
{ 
	pinMode(pwm2,PWM);
	pinMode(pwm1,PWM);
	pinMode(hongngoai, INPUT_PULLUP);
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	Serial1.begin(9600);
}

void loop()
{	if ((millis()<2000) || (millis()>3000 && millis()<5000)) {                                                                                                 
		pwmWrite(pwm1, i);
		pwmWrite(pwm2, i);
		digitalWrite(PA0, LOW);
		digitalWrite(PA3, LOW);
	}
	else if ((millis()>2000) && (millis()<3000)) {
		pwmWrite(pwm1, i);
		pwmWrite(pwm2, i-j);
		digitalWrite(PA0, LOW);
		digitalWrite(PA3, LOW);
	}
	else {
		pwmWrite(pwm1,0);
		pwmWrite(pwm2,0);
	} 
  delay(10);
	/* i = i + 10000; */
	/* if (i>65535) i=65535; */
	/* j = j - 1000; */
	/* if (j<0) j=0; */

	/* read_ESP8266(); */
	/* kiemtrahang(); */
	/* kiemtravatcan(); */
	/* if (millis()-last>=1500) { */
	/* 	send_Data(); */
	/* 	last=millis(); */
	/* } */
}

void kiemtrahang(void){
	if (digitalRead(hongngoai)==0){
		hang="1";
	}
	if (digitalRead(hongngoai)==1) {
		hang="0";
	}  
}

void kiemtravatcan(void){
	unsigned long duration;
	digitalWrite(trig,0);
	delayMicroseconds(2);
	digitalWrite(trig,1);
	delayMicroseconds(5);
	digitalWrite(trig,0);
	duration = pulseIn(echo,HIGH);
	khoangcach = int((duration/2)/29.412);
	if (khoangcach <= 20){
		vatcan= "1";
	}
	else {
		vatcan="0";
	}
	delay(200);
}

void send_Data(void){
	Json(String(hang), String(vatcan));
}

void Json(String thamso1, String thamso2){
	DataSend="";
	DataSend= "{\"hang\":\"" + String(thamso1) + "\"," +
			 "\"vatcan\":\"" + String (thamso2)+ "\"}";
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
