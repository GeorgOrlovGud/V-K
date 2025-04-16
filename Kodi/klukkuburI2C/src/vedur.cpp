#include <WiFi.h>
#include <HTTPClient.h>

namespace VEDUR {
    const char* vedurEndpoint = "https://xmlweather.vedur.is/?op_w=xml&type=obs&lang=en&view=xml&ids=1&params=R";

    bool rignir() {
        HTTPClient http;
        http.begin(vedurEndpoint);
        int httpResponse = http.GET();

        if (httpResponse != 200) {
            Serial.print("HTTP error: ");
            Serial.println(httpResponse);
            http.end();
            return false;
        }

        String payload = http.getString();
        Serial.println("Received payload:");
        Serial.println(payload);

        http.end();

        //Finna <R> taggið og ná í gildið í því
        int rStart = payload.indexOf("<R>");
        int rEnd = payload.indexOf("</R>");

        if (rStart != -1 && rEnd != -1 && rEnd > rStart) {
            String rValue = payload.substring(rStart + 3, rEnd);
            float precipitation = rValue.toFloat();

            Serial.print("Precipitation val: ");
            Serial.println(precipitation);

            return precipitation > 0.0;
        } else {
            Serial.println("Fer ekki í <R> loopu");
            return false;
        }
    }
}
