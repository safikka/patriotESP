#include <WiFi.h>
String apiKey = "";                               //API Key Patriot
String alamatWeb = "webpatriot/input?key=";

const char* ssid = "nais";                                    //ini nama wifinya
const char* pass = "safik123";                                //ini password wifinya
const char* server = "webpatriot";

WiFiClient client;
int adc;                                                      //variabel dummy

void setup() {
  Serial.begin(115200);
  delay(10);
  konekWifi();
}

void loop() {
  adc = random(50,100);
  kirimData();
  
  Serial.print("adc: ");                                      //cek dummy doang
  Serial.println(adc);
  delay(1000);
}

void konekWifi(){
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi terkoneksi");
}

void kirimData(){

  String alamatPost = alamatWeb + apiKey;
  if (client.connect(server,80)){
    alamatPost +="&value=";
    alamatPost += String(adc);                                   //ganti ke variabel sensornya
    alamatPost += "\r\n\r\n";

    client.print("GET " + alamatPost + " HTTP/1.1\r\n");
    client.print("Host: " + server + "\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(alamatPost.length());
    client.print("\n\n");
    client.print(alamatPost);
  }
  Serial.print(alamatPost);
}
