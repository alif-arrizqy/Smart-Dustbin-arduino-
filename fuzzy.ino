

void fuzzy_logic() {
  int in_ultra = avg;
  int in_mq = PPM;
  //--------------------------------------

  fuzzy->setInput(1, in_ultra);
  fuzzy->setInput(2, in_mq);
  fuzzy->fuzzify();


  int output = fuzzy->defuzzify(1);
  //  analogWrite(pin_led , out_led);

  //--------------------------------------

  Serial.print("pot1    ");
  Serial.print(in_ultra);  Serial.println("  bit");
  Serial.print("pot2    ");
  Serial.print(in_mq);  Serial.println("  bit");

  //---------------------

  Serial.print(in_ultra);   Serial.print(" ");
  Serial.println(in_mq);
  Serial.println(" ");

  Serial.print("Result output: ");
  Serial.println(output);

  if(output >= 70){
    Serial.println("Sangat Aman");
  } else if (output >= 50 && output <= 69){
    Serial.println("Terisi");
  } else if (output >= 30 && output <= 49) {
    Serial.println("Penuh");
  } else if (output >= 0 && output <= 29) {
    Serial.println("Sangat Penuh");
  }
  
}
