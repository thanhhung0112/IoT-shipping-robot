void compute_pwm(int theta, float mcu, bool flag, double & pwm1, double & pwm2) {
  double loss;
  loss = 1 + abs(theta - mcu) / 90; // loss has the value from 1 to 2 correspondence 0 to 90 (error between theta and mcu)
  double ratio;
  ratio = 1 + pow(loss, 3) * log(loss);
  if (theta - mcu > 0){
    pwm1 = pwm1/ratio; // turn the left
  }
  else if (theta - mcu < 0){
    pwm2 = pwm2/ratio; // turn the right
  }
}

void setup(){
  Serial.begin(9600);
}
void loop(){
  int theta; // get the specified value in the specified stage such as 0 degree in stage 1, 90 degree in stage 2, etc
  float mcu; // the value which the mcu sensor returns
  bool flag; // set to 1 when encountering obstacle
  double pwm1=80; // pwm pulse for the left motor
  double pwm2=80; // pwm pulse for the right motor
  compute_pwm(theta, mcu, flag, pwm1, pwm2);
  if (flag != 1) {
    // generate pulse
    // flag == 1 when the robot encountered any obstacle (workers), then do not generate pulse until the flag bool variable becomes 0 again
  }
}