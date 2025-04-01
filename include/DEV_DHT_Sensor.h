#ifndef DEV_DHT_SENSOR_H
#define DEV_DHT_SENSOR_H

#include <DHT_U.h>

#ifdef EZSTARTKIT_WIRE_H
#define DHT_PIN EZSTARTKIT_IO7
#else
// Define your DHT sensor pin
#define DHT_PIN -1
#endif

#define DHT_TYPE DHT11

DHT_Unified dht(DHT_PIN, DHT_TYPE);

bool dhtTemperatureFlag = false;
bool dhtHumidityFlag = false;
float currentTemperature = 0.0;
float currentHumidity = 0.0;

struct DEV_TemperatureSensor : Service::TemperatureSensor {

    // reference to the Current Temperature Characteristic
    SpanCharacteristic *temperature;                         
    sensors_event_t event;
    uint32_t dhtUpdatePeriod_MS;
    sensor_t sensor;
    float dhtTemperatureOffset;

    DEV_TemperatureSensor() : Service::TemperatureSensor() {

        dhtTemperatureOffset = -2.0;
        
        // Initialize the device.
        dht.begin();

        dht.temperature().getSensor(&sensor);
        
        // The unit of min_delay is microsecond, so cast it to millisecond by diving 1000.
        // To avoid the error reading, just set it longer than the min_delay by timing 5.
        dhtUpdatePeriod_MS = sensor.min_delay / 1000 * 5;
    
        dht.temperature().getEvent(&event);

        // Instantiate the CurrentTemperature Characteristic
        temperature = new Characteristic::CurrentTemperature(25.0);
        temperature->setRange(0.0, 100.0);
        

        LOG0(F("Temperature Sensor has been initialized!\n")); 
    }

    void loop() {

        // Check time elapsed since last update and proceed only if greater than min_delay of the sensor
        if (temperature->timeVal() > dhtUpdatePeriod_MS) {
            
            // Get temperature event and print its value.            
            dht.temperature().getEvent(&event);

            if (isnan(event.temperature) || event.temperature + dhtTemperatureOffset > sensor.max_value) {                      
                temperature->setVal(99.9);
                dhtTemperatureFlag = false;
                LOG0(F("Error reading temperature!\n"));
            }
            else {                
                if (temperature->getNewVal<float>() != event.temperature + dhtTemperatureOffset) { 

                    temperature->setVal(event.temperature + dhtTemperatureOffset);
                    currentTemperature = temperature->getVal<float>();
                    dhtTemperatureFlag = true;                                               
                    
                    LOG2(F("Temperature has been updated to "));
                    LOG2(temperature->getVal<float>());
                    LOG2(F("°C\n"));
                }
            }
        }
      } // loop

};

struct DEV_HumiditySensor : Service::HumiditySensor {

    // Reference to the Current Relative Humidity Characteristic
    SpanCharacteristic *humidity;                         
    sensors_event_t event;
    uint32_t dhtUpdatePeriod_MS;
    sensor_t sensor;
    
    DEV_HumiditySensor() : Service::HumiditySensor() {

        // Initialize the device
        dht.begin();
        
        dht.humidity().getSensor(&sensor);

        // The unit of min_delay is microsecond, so cast it to millisecond by diving 1000.
        // To avoid the error reading, just set it longer than the min_delay by timing 5.
        dhtUpdatePeriod_MS = sensor.min_delay / 1000 * 5;
        
        dht.humidity().getEvent(&event);
        
        humidity = new Characteristic::CurrentRelativeHumidity(50.0);       
        humidity->setRange(0.0, 100.0);
        
        LOG0(F("Humidity Sensor has been initialized!\n"));           

    }

    void loop() {
    
        if (humidity->timeVal() > dhtUpdatePeriod_MS) {

            // float hum = humidity->getVal<float>() + 0.5;
            // if (hum > 81.0) {
            //     hum = 20.0;
            // }
            // humidity->setVal(hum);
            // LOG0("\nhumidity: ");
            // LOG0(humidity->getVal<float>());
            // LOG0("\n");
            // currentHumidity = hum;
            dht.humidity().getEvent(&event);

            if (isnan(event.relative_humidity) || event.relative_humidity > sensor.max_value) {
                humidity->setVal(sensor.max_value);
                dhtHumidityFlag = false;
                LOG0(F("Error reading humidity!\n")); 
            }
            else {
                if (humidity->getVal<float>() != event.relative_humidity) {
                    
                    humidity->setVal(event.relative_humidity);
                    currentHumidity = humidity->getVal<float>();
                    dhtHumidityFlag = true;

                    LOG2("Humidity Update: ");
                    LOG2(humidity->getVal<float>());
                    LOG2("\n");
                } 
            }
        }
    } 
  
};

#endif // DEV_DHT_SENSOR_H