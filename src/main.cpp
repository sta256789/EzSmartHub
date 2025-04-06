#include <Arduino.h>
#include <HomeSpan.h>
#include "EzStartKit_Wire.h"
#include "OpenWeather_Service.h"
#include "Web_Services.h"
#include "DEV_DHT_Sensor.h"
#include "DEV_Relay.h"
#include "DEV_NEOPixel.h"
#include "DEV_Cooler.h"
#include "DEV_OLED.h"

// Built-in Button
#define BUTTON_BUILT_IN 0

uint32_t time_now = millis();

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    // HomeSpan    
    homeSpan.setControlPin(BUTTON_BUILT_IN);
    homeSpan.setStatusPin(EZSTARTKIT_IO6);
    homeSpan.setStatusAutoOff(10);    

    homeSpan.setConnectionCallback(webServicesUpdate);  
    homeSpan.setStatusCallback(loadingSceneDisplay);
    homeSpan.begin(Category::Bridges, "HomeSpan Bridge");

    // This first Accessory is the new "Bridge" Accessory.  
    // It contains no functional Services, just the Accessory Information Service.
    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Temperature Sensor");
    new DEV_TemperatureSensor();

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Humidity Sensor");
    new DEV_HumiditySensor();

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Relay Button");
    new DEV_Relay(EZSTARTKIT_IO13);

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Neo Pixels");
    new NeoPixel_RGB(0);

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Cooler");
    new DEV_Cooler(EZSTARTKIT_IO5);

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("OLED Button");
    new DEV_OLED(EZSTARTKIT_IO15);  
}

void loop() {
    // put your main code here, to run repeatedly:
    homeSpan.poll();

    if (millis() - time_now > webServicesUpdatePeriod_MS) {
        time_now = millis();

        webServicesUpdate();
    }
}
