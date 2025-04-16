#ifndef WEB_SERVICES_H
#define WEB_SERVICES_H

const uint32_t webServicesUpdatePeriod_MS = 1800000;
uint32_t webServicesLastUpdateTime_MS = millis();

#ifndef OPENWEATHER_SERVICE_H
#include "NTP_Service.h"
void webServicesUpdate(int count = 0) {
    webServicesLastUpdateTime_MS = millis();
    clockUpdate();
}
#else
void webServicesUpdate(int count = 0) {
    webServicesLastUpdateTime_MS = millis();
    weatherUpdate();
}
#endif

#endif