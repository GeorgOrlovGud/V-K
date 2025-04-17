#include <ThingSpeak.h>
#include <WiFi.h>
#include <Wire.h>

#include "WiFiListen.h"

const int ACTUATOR_PIN = 17;
bool isClosed = false;

void setup(){
    Serial.begin(115200);
    delay(1000);

    int setupTime = 45; //sekúndur

    Wire.begin();

    //init pinnan
    pinMode(ACTUATOR_PIN, OUTPUT);
    digitalWrite(ACTUATOR_PIN, LOW);

    //init WiFi og ThingSpeak
    THINGSPEAK::SetupWiFi(setupTime);
    THINGSPEAK::setup_ThingSpeak();
}

//Næstu tvö föll eru til svo ég geti kallað á þau ef, og einungis ef þess þarf
void closeAct(){
    Serial.println("Lokar Glugga.");
    isClosed = true;
}

void openAct(){
    Serial.println("Opnar glugga");
    isClosed = false;
}


void loop(){
    float hiti = THINGSPEAK::readHiti();
    bool rign = THINGSPEAK::readRign();
    bool hava = THINGSPEAK::readHava();
    Serial.println("Hitastig: " + String(hiti));
    Serial.println(String("Er að rigna? ") + String(rign ? "Já" : "Nei"));
    Serial.println("Er of hátt? " + String(hava ? "Já" : "Nei"));

    //Á að loka?
    bool adLoka = (hiti < 18) || rign || hava;

    //Kallar á föll sem loka og opna gluggan ef og einungis ef þess þarf
    if(adLoka && !isClosed){closeAct();}
    else if (!adLoka && isClosed){openAct();}

    //Heldur glugganum lokuðum/opnuðum
    if (isClosed)
    {
        digitalWrite(ACTUATOR_PIN, HIGH);
    }
    else
    {
        digitalWrite(ACTUATOR_PIN, LOW);
    }
    
    
    
    delay(60000);//60000 = 1 mínúta
    Serial.println("");
}