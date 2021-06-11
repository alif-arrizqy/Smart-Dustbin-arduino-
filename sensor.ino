//void sensor() {
//  //  kiri--------------------------------
//  digitalWrite(trigL, LOW);
//  delay(100);
//
//  digitalWrite(trigL, HIGH);
//  delay(100);
//  digitalWrite(trigL, LOW);
//
//  duration = pulseIn(echoL, HIGH);
//
//  distanceL = duration * 0.034 / 2;
////  Serial.print("Kiri: ");
////  Serial.println(distanceL);
//  //  delay(300);
//
//  //  tengah-------------------------------
//  digitalWrite(trigC, LOW);
//  delay(100);
//
//  digitalWrite(trigC, HIGH);
//  delay(100);
//  digitalWrite(trigC, LOW);
//
//  duration = pulseIn(echoC, HIGH);
//
//  distanceC = duration * 0.034 / 2;
//  Serial.print("Tengah: ");
//  Serial.println(distanceC);
////    delay(300);
//
//  // kanan--------------------------------
//  digitalWrite(trigR, LOW);
//  delay(100);
//
//  digitalWrite(trigR, HIGH);
//  delay(100);
//  digitalWrite(trigR, LOW);
//
//  duration = pulseIn(echoR, HIGH);
//
//  distanceR = duration * 0.034 / 2;
////  Serial.print("Kanan: ");
////  Serial.println(distanceR);
//  //  delay(300);
//
//  //  rata-rata----------------------------------
//  avg = (distanceL + distanceC + distanceR) / 3;
////  Serial.print("Rata-rata: ");
////  Serial.println(avg);
//  //}
//
//  // gas metana----------------------------------
//  //float getMethanePPM() {
//  a0 = analogRead(A0); // get raw reading from sensor
//  v_o = a0 * 5 / 1023; // convert reading to volts
//  R_S = (5 - v_o) * 1000 / v_o; // apply formula for getting RS
//  PPM = pow(R_S / R_0, -2.95) * 1000; //apply formula for getting PPM
////  Serial.print("PPM : ");
////  Serial.println(PPM);
//  //  return PPM; // return PPM value to calling function
//}
