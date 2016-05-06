#include "DeviceIndependentInterfaces.h"
#include "Esp8266AWSImplementations.h"

#include <ESP8266WiFi.h>

const unsigned long maxTimeout = 5000;

Esp8266HttpClient::Esp8266HttpClient() {}

char* Esp8266HttpClient::send(const char* request, const char* serverUrl,
        int port) {
    /* Arduino String to build the response with. */
    String responseBuilder = "";
    if (client.connect(serverUrl, port)) {
        /* Send the request */
        client.println(request);

        unsigned long timeout = millis();
        while (client.available() == 0) {
            if (millis() - timeout > maxTimeout) {
                client.stop();
                /* Timeout. */
                return 0;
            }
        }

        if (client.available()) {
            responseBuilder += client.readString();
        }
        client.stop();
    } else {
        client.stop();
        /* Error connecting. */
        return 0;
    }
    /* Copy responseBuilder into char* */
    int len = responseBuilder.length();
    char* response = new char[len + 1]();
    responseBuilder.toCharArray(response, len + 1);
    return response;
}

bool Esp8266HttpClient::usesCurl() {
    /* Does not use curl command. */
    return false;
}

Esp8266DateTimeProvider::Esp8266DateTimeProvider() {
    /* These are initialized to defaults. The defaults will cause the request
     * to fail, but the AWS Services response will contain the correct time
     * which will be fed to sync(). */
    year = 2000;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;

    syncedTime = 0;
}

const char* Esp8266DateTimeProvider::getDateTime() {
    const int secondsPerMinute = 60;
    const int secondsPerHour = secondsPerMinute * 60;
    const long int secondsPerDay = secondsPerHour * 24;
    /* Determine how many seconds have passed since the last sync, break those
     * seconds down into days/hours/minutes/seconds, then form the new time
     * string. */
    long int newSecond = ((millis() - syncedTime) / 1000) + second
            + (secondsPerMinute * minute) + (secondsPerHour * hour)
            + (secondsPerDay * day);
    int newDay = newSecond / secondsPerDay;
    newSecond = newSecond % secondsPerDay;
    int newHour = newSecond / secondsPerHour;
    newSecond = newSecond % secondsPerHour;
    int newMinute = newSecond / secondsPerMinute;
    newSecond = newSecond % secondsPerMinute;

    /* Without cumbersome data about how many days a month we cannot factor the
     * extra time into more months. AWS Services give different errors that do
     * not provide us with the current time if the date is invalid rather than
     * innacurate. However, going past the number of days in a month (i.e
     * giving 30 for February) is valid, so long as the days does not exceed
     *  31. */
    newDay = newDay > 31 ? 31 : newDay;

    /* Copy the values to dateTime and return it. */
    sprintf(dateTime, "%04d%02d%02d%02d%02d%02d", year, month, newDay, newHour,
            newMinute, newSecond);

    return dateTime;
}

bool Esp8266DateTimeProvider::syncTakesArg(void) {
    return true;
}

void Esp8266DateTimeProvider::sync(const char* dateTime) {
    /* If given a null dateTime, do nothing. */
    if (dateTime) {
        /* Set synced time to the number of milliseconds since the sketch
         * started. */
        syncedTime = millis();
        /* Copy each substring into the buffer then convert it to an integer. */
        char buffer[5];
        // Year
        strncpy(buffer, dateTime, 4);
        year = atoi(buffer);
        memset(buffer, '\0', 5);
        // Month
        strncpy(buffer, dateTime + 4, 2);
        month = atoi(buffer);
        memset(buffer, '\0', 5);
        // Day
        strncpy(buffer, dateTime + 6, 2);
        day = atoi(buffer);
        memset(buffer, '\0', 5);
        // Hour
        strncpy(buffer, dateTime + 8, 2);
        hour = atoi(buffer);
        memset(buffer, '\0', 5);
        // Minute
        strncpy(buffer, dateTime + 10, 2);
        minute = atoi(buffer);
        memset(buffer, '\0', 5);
        // Second
        strncpy(buffer, dateTime + 12, 2);
        second = atoi(buffer);
        memset(buffer, '\0', 5);
        
        /* If these values come out as 0, change them to valid AWS date values
         * (i.e. cannot have month 0). */
        year = year ? year : 2000;
        month = month ? month : 1;
        day = day ? day : 1;
    }
}
