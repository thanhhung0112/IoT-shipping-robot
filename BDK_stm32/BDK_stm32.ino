const int pwm1=PA1;
const int pwm2=PA2;
int i=0;
int j=0;
int pulse_val1;
int pulse_val2;
const float mcu; // the value which the mcu sensor returns
const int theta; // get the specified value in the specified stage such as 0 degree in stage 1, 90 degree in stage 2, etc

void compute_ratio(int theta, float mcu) {
	double loss;
	loss = 1 + abs(theta - mcu) / 90; // loss has the value from 1 to 2 correspondence 0 to 90 (error between theta and mcu)
	double ratio;
	ratio = pow(loss, 3) * log(loss);
	return ratio;
}

void setup() {
	pinMode(pwm2, PWM);
	pinMode(pwm1, PWM);
	Serial.begin(9600);
}

void loop() {
	ratio = compute_ratio(theta, mcu);
	pulse_val1 = (int) (i/(1 + (1 + abs(theta-mcu+0.0001) / (theta-mcu+0.0001))*ratio/2));
	pulse_val2 = (int) (j/(1 + (1 - abs(theta-mcu-0.0001) / (theta-mcu-0.0001))*ratio/2));
	pwmWrite(pwm1, pulse_val1);
	pwmWrite(pwm2, pulse_val2);
	digitalWrite(PA0, LOW);
	digitalWrite(PA3, LOW);
	i = i + 1000;
	j = j + 1000;
	delay(50);
	if (i > 65535) i = 65535;
	if (j > 65535) j = 65535;
}
