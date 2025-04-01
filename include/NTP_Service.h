#ifndef NTP_SERVICE_H
#define NTP_SERVICE_H

#include <time.h>

const int timeZone = 8;
const int daylightOffset_sec = 0;
bool ntpAvailableFlag = false;

void printLocalTime() {
    time_t now;
    struct tm timeInfo;

    time(&now);
    localtime_r(&now, &timeInfo);

    if (!getLocalTime(&timeInfo)) {
        LOG0(F("No time available (yet)\n"));
        return;
    }

    char strftime_buf[32];
    strftime(strftime_buf, sizeof(strftime_buf), "%a, %d %b %Y %r\n", &timeInfo);
    LOG0(strftime_buf);
}

void timeAvailable() {
    ntpAvailableFlag = true;
    LOG0(F("Got time adjustment from NTP!\n"));
    printLocalTime();
}

void clockUpdate() {
    
    const char* ntpServer = "pool.ntp.org";    
    const long  gmtOffset_sec = timeZone * 3600;    

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    timeAvailable();
}

#endif // NTP_SERVICE_H