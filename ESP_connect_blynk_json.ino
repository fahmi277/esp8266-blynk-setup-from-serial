
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>

//char auth[] = "DSBta0R2VBVulKPadt2EteZtLnfy1BoE";
//char auth[] = "9pJkxFN4ySANF4FMfwjuMHJ1jhaADLxN";
//char auth[] = "OnwTACKazZ3nFl_2xqTzQK5B_Wd2rAR5";
//char auth[] = "uJdYEPlwrH5KN6AMf1u-HrIse3TST_yM";

// ================== new token ====================//

char auth[] = "jr4JZbDvkPOI-6C7Ra15UTvZsYsIxkYC";
//char auth[] = "ddjxRwECbWxlXM0NlCnFqrk-5b2xB9Br"
//char auth[] = "XDaX1KIbTMgZ_gBZd6nCrEiePHn6CeyZ"
//char auth[] = "kYgpQYqBSnPadQ_H3XRTwL51eAQpNbHn"
//char auth[] = "yURcMdvtsnhI9Y24isBbfjq1pkY3mhXi"

// ================== new token ====================//

//

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WAKANDA";
char pass[] = "jombloelit";
float dataVoltage, dataArus, dataSinyal;


boolean setValue = false;
boolean setData = false;
void setup()
{
  // Debug console
  Serial.begin(9600);
  while (setValue == false)
  {
    if (Serial.available()) {
      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(Serial);
      if (root == JsonObject::invalid())
        return;
      String dataAuth = root["auth"];
      String dataSsid = root["ssid"];
      String dataPass = root["pass"];
      if (dataAuth != "") {

        const char* Auth = dataAuth.c_str();
        const char* Ssid = dataSsid.c_str();
        const char* Pass = dataPass.c_str();
        Blynk.begin(Auth, Ssid, Pass, "blynk-cloud.com", 8080);
        Serial.print("Password masuk");
        setValue = true;

      }
    }

  }
}

void loop()
{
  if (setValue)
  {

    if (Serial.available()) {
      //    Serial.write(mySerial.read());
      StaticJsonBuffer<1000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(Serial);
      if (root == JsonObject::invalid())
        return;
      float dataVoltage = root["voltage"];
      float dataArus = root["current"];
      float dataSinyal = root["sinyal"];

      Blynk.virtualWrite(V0, dataVoltage);
      Blynk.virtualWrite(V1, dataArus);
      Blynk.virtualWrite(V2, dataSinyal);
      Serial.println("Uploaded");
    }


    Blynk.run();
  }
}
