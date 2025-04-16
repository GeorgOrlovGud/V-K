#ifndef WiFiSpeak_
#define WiFiSpeak_
#include <string>

namespace THINGSPEAK{
    void SetupWiFi(float WiFiSetuptime);
    bool isConnected();
    void setup_ThingSpeak();
    void writeAll(float Hiti, float Raki, float Thrist, bool rain, bool isLoud);
}

#endif
