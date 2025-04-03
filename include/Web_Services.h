#ifndef WEB_SERVICES_H
#define WEB_SERVICES_H

const uint32_t webServicesUpdatePeriod_MS = 1800000;

#ifndef OPENWEATHER_SERVICE_H
#include "NTP_Service.h"
void webServicesUpdate(int num = 0) {
    clockUpdate();
}
#else
void webServicesUpdate(int num = 0) {
    weatherUpdate();
}
#endif

#endif