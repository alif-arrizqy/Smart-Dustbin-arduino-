//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiServer.h>

//Konfigurasi WiFi
//const char *ssid = "GalaxyA50s";
//const char *password = "galaxya50s";

//IP Address Server yang terpasang XAMPP
//const char *host = "projectsuizen.com";

//unsigned long lastmillis = millis();


/////////////////////////// ULTRASONIK ///////////////////////////
//kiri
const int trigL = D0; //d1
const int echoL = D1; //d0
//tengah
const int trigC = D2;//d3
const int echoC = D3; //d2
//kanan
const int trigR = D4; //d5
const int echoR = D5; //d4

long duration;
int distanceL, distanceC, distanceR;
float avg;
String result;


/////////////////////////// MQ-4 ///////////////////////////
const byte MQ4_Pin = A0; //MQ4 A0 pin
const int R_0 = 945; //Change this to your own R0 measurements
float a0;
float v_o;
float R_S;
float PPM;

//Fuzzy
#include <Fuzzy.h>
Fuzzy *fuzzy = new Fuzzy();

// FuzzyInput ultrasonik
FuzzySet *kosong          = new FuzzySet(70, 70, 80, 90);
FuzzySet *terisi          = new FuzzySet(50, 55, 60, 60);
FuzzySet *penuh           = new FuzzySet(30, 35, 40, 50);
FuzzySet *sangatpenuh     = new FuzzySet(15, 20, 25, 30);

// FuzzyInput gas metana mq4
FuzzySet *tdkbahaya       = new FuzzySet(0, 0, 300, 500);
FuzzySet *aman            = new FuzzySet(400, 500, 700, 900);
FuzzySet *cukupaman       = new FuzzySet(800, 800, 900, 1000);
FuzzySet *bahaya          = new FuzzySet(900, 2000, 5000, 10000);

// FuzzyOutput
FuzzySet *sangataman      = new FuzzySet(70, 70, 80, 90);
FuzzySet *aman1           = new FuzzySet(50, 55, 60, 60);
FuzzySet *warning         = new FuzzySet(30, 35, 40, 50);
FuzzySet *penuh1          = new FuzzySet(15, 20, 25, 30);

int value = 0;
void setup() {
  // put your setup code here, to run once:
  ////////////////////////////////// CEK KONEKSI /////////////////////////
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//  Serial.println("");

//  Serial.print("Connecting");
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }

  //Jika koneksi berhasil, maka akan muncul address di serial monitor
//  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());


  pinMode(trigL, OUTPUT);
  pinMode(trigC, OUTPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(echoC, INPUT);
  pinMode(echoR, INPUT);
  Serial.begin(9600);

  //Fuzzy Input dan Output
  //--------------------------------------
  // FuzzyInput
  FuzzyInput *ultra = new FuzzyInput(1);

  ultra->addFuzzySet(kosong);
  ultra->addFuzzySet(terisi);
  ultra->addFuzzySet(penuh);
  ultra->addFuzzySet(sangatpenuh);
  fuzzy->addFuzzyInput(ultra);


  // FuzzyInput
  FuzzyInput *mq = new FuzzyInput(2);

  mq->addFuzzySet(tdkbahaya);
  mq->addFuzzySet(aman);
  mq->addFuzzySet(cukupaman);
  mq->addFuzzySet(bahaya);
  fuzzy->addFuzzyInput(mq);


  // FuzzyOutput
  FuzzyOutput *out = new FuzzyOutput(1);

  out->addFuzzySet(sangataman);
  out->addFuzzySet(aman1);
  out->addFuzzySet(warning);
  out->addFuzzySet(penuh1);
  fuzzy->addFuzzyOutput(out);
  //--------------------------------------


  //Inferensi atau Base Rules Fuzzy
  //--------------------------------------


  // Building FuzzyRule////////////////////////////////////////////////////////////////// 1
  FuzzyRuleAntecedent *kosong_tb = new FuzzyRuleAntecedent();
  kosong_tb->joinWithAND(kosong, tdkbahaya);

  FuzzyRuleConsequent *output1 = new FuzzyRuleConsequent();
  output1->addOutput(sangataman);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, kosong_tb, output1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 2
  FuzzyRuleAntecedent *kosong_am = new FuzzyRuleAntecedent();
  kosong_am->joinWithAND(kosong, aman);

  FuzzyRuleConsequent *output2 = new FuzzyRuleConsequent();
  output2->addOutput(sangataman);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, kosong_am, output2);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 3
  FuzzyRuleAntecedent *kosong_ca = new FuzzyRuleAntecedent();
  kosong_ca->joinWithAND(kosong, cukupaman);

  FuzzyRuleConsequent *output3 = new FuzzyRuleConsequent();
  output3->addOutput(aman1);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, kosong_ca, output3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 4
  FuzzyRuleAntecedent *kosong_bh = new FuzzyRuleAntecedent();
  kosong_bh->joinWithAND(kosong, bahaya);

  FuzzyRuleConsequent *output4 = new FuzzyRuleConsequent();
  output4->addOutput(penuh1);

  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, kosong_bh, output4);
  fuzzy->addFuzzyRule(fuzzyRule4);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 5
  FuzzyRuleAntecedent *terisi_tb = new FuzzyRuleAntecedent();
  terisi_tb->joinWithAND(terisi, tdkbahaya);

  FuzzyRuleConsequent *output5 = new FuzzyRuleConsequent();
  output5->addOutput(sangataman);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, terisi_tb, output5);
  fuzzy->addFuzzyRule(fuzzyRule5);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 6
  FuzzyRuleAntecedent *terisi_am = new FuzzyRuleAntecedent();
  terisi_am->joinWithAND(terisi, aman);

  FuzzyRuleConsequent *output6 = new FuzzyRuleConsequent();
  output6->addOutput(aman1);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, terisi_am, output6);
  fuzzy->addFuzzyRule(fuzzyRule6);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 7
  FuzzyRuleAntecedent *terisi_ca = new FuzzyRuleAntecedent();
  terisi_ca->joinWithAND(terisi, cukupaman);

  FuzzyRuleConsequent *output7 = new FuzzyRuleConsequent();
  output7->addOutput(warning);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, terisi_ca, output7);
  fuzzy->addFuzzyRule(fuzzyRule7);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 8
  FuzzyRuleAntecedent *terisi_bh = new FuzzyRuleAntecedent();
  terisi_bh->joinWithAND(terisi, bahaya);

  FuzzyRuleConsequent *output8 = new FuzzyRuleConsequent();
  output8->addOutput(penuh1);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, terisi_bh, output8);
  fuzzy->addFuzzyRule(fuzzyRule8);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *penuh_tb = new FuzzyRuleAntecedent();
  penuh_tb->joinWithAND(penuh, tdkbahaya);

  FuzzyRuleConsequent *output9 = new FuzzyRuleConsequent();
  output9->addOutput(warning);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, penuh_tb, output9);
  fuzzy->addFuzzyRule(fuzzyRule9);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *penuh_am = new FuzzyRuleAntecedent();
  penuh_am->joinWithAND(penuh, aman);

  FuzzyRuleConsequent *output10 = new FuzzyRuleConsequent();
  output10->addOutput(warning);

  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, penuh_am, output10);
  fuzzy->addFuzzyRule(fuzzyRule10);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *penuh_ca = new FuzzyRuleAntecedent();
  penuh_ca->joinWithAND(penuh, cukupaman);

  FuzzyRuleConsequent *output11 = new FuzzyRuleConsequent();
  output11->addOutput(warning);

  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, penuh_ca, output11);
  fuzzy->addFuzzyRule(fuzzyRule11);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *penuh_bh = new FuzzyRuleAntecedent();
  penuh_bh->joinWithAND(penuh, bahaya);

  FuzzyRuleConsequent *output12 = new FuzzyRuleConsequent();
  output12->addOutput(penuh1);

  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, penuh_bh, output12);
  fuzzy->addFuzzyRule(fuzzyRule12);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *sp_tb = new FuzzyRuleAntecedent();
  sp_tb->joinWithAND(sangatpenuh, tdkbahaya);

  FuzzyRuleConsequent *output13 = new FuzzyRuleConsequent();
  output13->addOutput(penuh1);

  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, sp_tb, output13);
  fuzzy->addFuzzyRule(fuzzyRule13);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *sp_am = new FuzzyRuleAntecedent();
  sp_am->joinWithAND(sangatpenuh, aman);

  FuzzyRuleConsequent *output14 = new FuzzyRuleConsequent();
  output14->addOutput(penuh1);

  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, sp_am, output14);
  fuzzy->addFuzzyRule(fuzzyRule14);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *sp_ca = new FuzzyRuleAntecedent();
  sp_ca->joinWithAND(sangatpenuh, cukupaman);

  FuzzyRuleConsequent *output15 = new FuzzyRuleConsequent();
  output15->addOutput(penuh1);

  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, sp_ca, output15);
  fuzzy->addFuzzyRule(fuzzyRule15);

  // Building FuzzyRule////////////////////////////////////////////////////////////////// 9
  FuzzyRuleAntecedent *sp_bh = new FuzzyRuleAntecedent();
  sp_bh->joinWithAND(sangatpenuh, bahaya);

  FuzzyRuleConsequent *output16 = new FuzzyRuleConsequent();
  output16->addOutput(penuh1);

  FuzzyRule *fuzzyRule16 = new FuzzyRule(16, sp_bh, output16);
  fuzzy->addFuzzyRule(fuzzyRule16);
  //--------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor();
  fuzzy_logic();
  delay(500);
  //  webserver();
  //  Serial.println(getMethanePPM());



}
