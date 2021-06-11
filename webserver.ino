//void webserver() {
//  // Proses Pengiriman -----------------------------------------------------------
//  delay(100);
//  ++value;
//
//
//  // Membaca Sensor --------------------------------------------------------------
//  sensor();
//  fuzzy_logic();
//
//
//  // Mengirimkan ke alamat host dengan port 80 ------------------------------------
//  WiFiClient client;
//  const int httpPort = 80;
//  if (!client.connect(host, httpPort)) {
//    Serial.println("connection failed");
//    return;
//  }
//
//  // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
//  String url = "/smartdustbin/save_sampah_organik/";
//  url += avg;
//  url += "/";
//  url += PPM;
//  url += "/";
//  url += result;
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//
//  // Mengirimkan Request ke Server -----------------------------------------------
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Connection: close\r\n\r\n");
//  unsigned long timeout = millis();
//  while (client.available() == 0) {
//    if (millis() - timeout > 1000) {
//      Serial.println(">>> Client Timeout !");
//      client.stop();
//      return;
//    }
//  }
//
//
//  // Read all the lines of the reply from server and print them to Serial
//  while (client.available()) {
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//  }
//
//  Serial.println();
//  Serial.println("closing connection");
//}
