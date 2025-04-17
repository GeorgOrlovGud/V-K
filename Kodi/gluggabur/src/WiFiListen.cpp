#include <WiFi.h>
#include <string>
#include <ThingSpeak.h>

WiFiClient client;

namespace THINGSPEAK{
    //ThingSpeak
    //Eins og ég sagði í hinu tækinu, bottar meiga alveg stela lyklinum.
    int channelNum = 2911199;
    const char* APIStr = "G6BU2OB8GJMNANXH";

    //Wifi client
    const char* ssid = "GoggiECE";
    const char* pw = "mammathin";

    //Það eru góðar ástæður til að initialize breyturnar hér, ef þú sklur ekki þá ertu ekki á mínu leveli.
    float hiti = 0;
    float raki = 0;
    float thrystingur = 0;
    bool rigning = 0;
    bool havadi = false;

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
        Serial.println("\n Tengt við WiFi: " + String(WiFi.localIP()));} 
        //😳😳😳 else 😳😳😳
        else {Serial.println("Náði ekki tengingu við WiFi");}
    }

    bool isConnected(){
        return WiFi.status() == WL_CONNECTED;
    }

    void setup_ThingSpeak(){
        ThingSpeak.begin(client);
    }

    float readHiti(){
        return ThingSpeak.readFloatField(channelNum, 1, APIStr);
    }

    //raki og þrýstingur ekki notað en þúst fokkit
    float readRaki(){
        return ThingSpeak.readFloatField(channelNum, 2, APIStr);
    }
    float readThryst(){
        return ThingSpeak.readFloatField(channelNum, 3, APIStr);
    }

    bool readRign(){
        if(ThingSpeak.readIntField(channelNum, 4, APIStr) == 1){return true;} 
        else {return false;}
    }

    bool readHava(){
        if (ThingSpeak.readIntField(channelNum, 5, APIStr) ==1){return true;}
        else {return false;}
    }
}