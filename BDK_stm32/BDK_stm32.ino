void compute_pwm(int theta, float mcu, bool flag, double & pwm1, double & pwm2) {
  double loss;
  loss = 1 + (theta - mcu) / 90;
  double ratio;
  ratio = 1 + pow(loss, 3) * log(loss);
  if (loss > 0){
    pwm1 = pwm1/ratio;
  }
  else if (loss < 0){
    pwm2 = pwm2/ratio;
  }
}

void setup(){
  double pwm1=80;
  double pwm2=80;
  int theta; // get the specified value in the specified stage such as 0 degree in stage 1, 90 degree in stage 2, etc
  float mcu; // the value which the mcu sensor returns
  bool flag; // set to 1 when encountering obstacle
  compute_pwm(theta, mcu, flag, pwm1, pwm2);
}
void loop(){
  if (flag != 1) {
    // generate pulse
    // flag == 1 when the robot encountered any obstacle (workers), then do not generate pulse until the flag bool variable becomes 0 again
  }
}