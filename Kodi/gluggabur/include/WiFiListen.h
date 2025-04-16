#ifndef WiFiListen_
#define WiFiListen_
#include <string>

namespace THINGSPEAK{
    void SetupWiFi(float WiFiSetuptime);
    bool isConnected();
    void setup_ThingSpeak();
    float readHiti();
    float readRaki();
    float readThryst();
    bool readRign();
    bool readHava();
}

#endif
