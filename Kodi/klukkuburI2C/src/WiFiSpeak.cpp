#include <WiFi.h>
#include <ThingSpeak.h>
#include <string>

WiFiClient client;

namespace THINGSPEAK{

    //Thingspeak client
    int channelNum = 2911199;
    String APIStr = "7HD1BPUBYL8FXSYH";

    //Wifi client
    const char* ssid = "GoggiECE";
    const char* pw = "mammathin";

    //Fall sem setur upp wifi'ið, keyra fyrst
    void SetupWiFi(float SetupTime){
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, pw);
        Serial.println("Tengist við Wi-Fi");     

        int k = 0;

        while (WiFi.status() != WL_CONNECTED && k < SetupTime) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print(".");
            k++;
        }

          //Segir á Serial Monitor hvort að tenging hafi heppnast
        if (WiFi.status() == WL_CONNECTED) {

        Serial.println("");
        Serial.println("Tengt við WiFi: " + String(WiFi.localIP()));} else {
            Serial.println("");
            Serial.println("Náði ekki tengingu við WiFi");
        }
    }

    bool isConnected(){
        return WiFi.status() == WL_CONNECTED;
    }

    void setup_ThingSpeak(){
        ThingSpeak.begin(client);
    }

    //Skrifa inní öll Fields á ThingSpeak
    void writeAll(float Hiti, float Raki, float Thrist, bool rain, bool isLoud){
        Serial.println("Tengist við ThingSpeak");
        if(isConnected() && client.connect(THINGSPEAK_URL, 80)){
            Serial.println("Kemst inní if setningu");
            ThingSpeak.setField(1, Hiti);
            ThingSpeak.setField(2, Raki);
            ThingSpeak.setField(3, Thrist);
            ThingSpeak.setField(4, rain);
            ThingSpeak.setField(5, isLoud);

            Serial.println("SSID er: " + String(ssid) +
            "\nWi-Fi lykilorð er: " + pw);

            int t = ThingSpeak.writeFields(channelNum, APIStr.c_str());
            if(t == 200) {
                Serial.println("Tókst að senda gögn");
            }
            else{
                Serial.println("Tókst ekki að senda gögn");
            }
        }else{
            Serial.println("Nær ekki að tengjast við ThingSpeak");
        }
    }
}
