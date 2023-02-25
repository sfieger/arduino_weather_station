void setup() {
  Serial.begin(9600);
}

void loop() {
  float v_out = analogRead(A0) * (5.0 / 1023.0);

  // v_s = 5.1 +- 0.25 * v_dc
  // v_dc is measured
  float v_dc = 4.8;
  float v_s = 5.1 - 0.0315 * v_dc;

  // pressure error band
  // +-1.5 kPa
  float p_err = 0.325;
  
  // temperature error band factors
  // t between -40C and   0C: -0.05 * t + 1
  // t between   0C and  85C: 1
  // t between  85C and 125C: 0.05 * t - 3.25
  // t_fac = 1 because we test indoors
  float t_fac = 1;

  // error = p_err * t_fac * 0.009 * v_s
  float error = p_err * t_fac * 0.009 * v_s;

  // v_out = v_s * (0.009 * p - 0.095) + error
  // solved for p in kPa
  float p = (5 * (-200 * error + 19 * v_s + 200 * v_out)) / (9 * v_s);
  // make it hPa because that is what we use in Germany
  p = p * 10;

  Serial.print("PRES: ");
  Serial.print(p, 0);
  Serial.println(" hPa"); 

  delay(2000);
}
