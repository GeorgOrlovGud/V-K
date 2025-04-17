#include <WiFi.h>
#include <HTTPClient.h>

namespace VEDUR {
    //Fokk já xml>json!!
    const char* vedurEndpoint = "https://xmlweather.vedur.is/?op_w=xml&type=obs&lang=en&view=xml&ids=1&params=R";

    bool rignir() {
        HTTPClient http;
        http.begin(vedurEndpoint);
        int httpResponse = http.GET();

        //Hefur aldrei gerst, ef þetta gerist ekki hringja í mig
        if (httpResponse != 200) {
            Serial.print("HTTP error: ");
            Serial.println(httpResponse);
            http.end();
            return false;
        }

        String payload = http.getString();
        Serial.println("Received payload:");
        Serial.println(payload);

        //loka clientinum
        http.end();

        //Finna <R> töggin og ná í gildið milli þeirra
        int rStart = payload.indexOf("<R>");
        int rEnd = payload.indexOf("</R>");

        if (rStart != -1 && rEnd != -1 && rEnd > rStart) {
            String rValue = payload.substring(rStart + 3, rEnd);
            float precipitation = rValue.toFloat();

            Serial.print("Precipitation val: "); //Hef aldrei heyrt þetta orð fyrr en núna en ætla alltaf að nota það
            Serial.println(precipitation);

            return precipitation > 0.0;
        } else {
            //Þetta mun aldrei gerast, ef þetta gerist þá ertu í mjög slæmum draum
            Serial.println("Fer ekki í <R> loopu");
            return false;
        }
    }
}
