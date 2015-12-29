#ifndef Esp8266AWSIMPLEMENTATIONS_H_
#define Esp8266AWSIMPLEMENTATIONS_H_

#include "DeviceIndependentInterfaces.h"
/* The WiFi Client is defined in this header. */
#include <ESP8266WiFi.h>

/* HttpClient implementation to be used on the Esp8266 device. */
class Esp8266HttpClient: public IHttpClient {
    WiFiClient client;
public:
    Esp8266HttpClient();
    /* Send http request and return the response. */
    char* send(const char *request, const char* serverUrl, int port);
    /* Returns false. Client uses raw http/https. */
    bool usesCurl(void);
};

/* IDateTimeProvider implementation to be used on the Esp8266 device. */
class Esp8266DateTimeProvider: public IDateTimeProvider {
    /* These values set as default in constructor and updated in sync() */
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    /* The time in seconds that the Esp8266DateTimeProvider was last synced. */
    unsigned long syncedTime;
    /* The time as a cstring in yyyyMMddHHmmss format. Is written to within and
     * returned by getDateTime(). */
    char dateTime[15];
public:
    Esp8266DateTimeProvider();
    /* Retrieve the current GMT date and time in yyyyMMddHHmmss format. On
     * first call this will return a default date. sync() must then be called
     * with the current date. */
    const char* getDateTime(void);
    /* Returns true. Esp8266 requires an argument for sync because the device
     * does not intenally handle current time. */
    bool syncTakesArg(void);
    /* Synchronizes the Esp8266DateTimeProvider's time given the current time
     * in yyyyMMddHHmmss format. */
    void sync(const char* dateTime);
};


bool Esp8266_Wifi_Setup(char* pSSID, char* pPassword);
void printWifiStatus();

#endif /* Esp8266AWSIMPLEMENTATIONS_H_ */
