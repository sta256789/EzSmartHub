#ifndef DEV_COOLER_H
#define DEV_COOLER_H

#ifndef EZSTARTKIT_WIRE_H
#define LED_BUILTIN 2
#endif

#include <IRremote.hpp>
#include "CoolerData.h"

bool displayUnitsFlag = false;

enum TargetStates {
    AUTO = 0, // It will be disabled since we don't have the heater.
    HEAT = 1, // It will be disabled since we don't have the heater.
    COOL = 2, // A cooler only have COOL target state
};

enum CurrentStates {
    INACTIVE = 0,
    IDLE = 1,
    HEATING = 2, // It will be disabled since we don't have the heater.
    COOLING = 3 
};

enum DisplayUnits {
    CELSIUS = 0,
    FAHRENHEIT = 1 
};

enum SwingMode {
    SWING_DISABLED = 0,
    SWING_ENABLED = 1
};

struct DEV_Cooler : Service::HeaterCooler {

    uint32_t statusUpdatePeriod_MS;
    uint32_t lastUpdateTemperature;    

    // Setup the characteristic objects
    SpanCharacteristic *powerState;
    SpanCharacteristic *temperature;
    SpanCharacteristic *currentCoolerState;
    SpanCharacteristic *targetCoolerState;

    // A cooler must include cooling threshold temperature
    SpanCharacteristic *coolingThresholdTemperature;

    // Optional
    SpanCharacteristic *displayUnits;
    SpanCharacteristic *swingMode;
    SpanCharacteristic *rotationSpeed;
    
    DEV_Cooler(int irSendPin) : Service::HeaterCooler() {

        IrSender.begin(irSendPin);

        statusUpdatePeriod_MS = 5000;
        lastUpdateTemperature = millis();

        powerState = new Characteristic::Active();

        temperature = new Characteristic::CurrentTemperature(25.0);

        currentCoolerState = new Characteristic::CurrentHeaterCoolerState(IDLE);

        // The initial value must set to COOL
        targetCoolerState = new Characteristic::TargetHeaterCoolerState(COOL);        

        coolingThresholdTemperature = new Characteristic::CoolingThresholdTemperature(26.0, true);
        coolingThresholdTemperature->setRange(16, 31, 1);

        displayUnits = new Characteristic::TemperatureDisplayUnits(CELSIUS);

        swingMode = new Characteristic::SwingMode(SWING_DISABLED);
        
        rotationSpeed = new Characteristic::RotationSpeed(0.0);        
        rotationSpeed->setRange(0.0, 100.0);

        // Setup the valid values for characteristics
        currentCoolerState->setValidValues(2, IDLE, COOLING);        
        targetCoolerState->setValidValues(1, COOL);
        
        // Initialization message    
        LOG0("Configuring the Cooler!");   
        LOG0("\n");
    }

    boolean update() override {

        // Power
        if (powerState->updated()) {
            if (!powerState->getNewVal()) { 
                sendIrCommand(POWEROFF);           
                LOG1("Set the powerState OFF!\n");
            } 
            else {
                sendIrCommand(POWERON);
                LOG1("Set the powerState ON!\n");
            }          
        }

        // Force targetCoolerState to keep COOL
        if (targetCoolerState->updated()) {
            if (targetCoolerState->getNewVal() != COOL) {
                targetCoolerState->setVal(COOL);
                LOG1("Set targetCoolerState to COOL\n");
            }
        }
        
        // Only displays on the OLED, the Homekit is not allowed to show °F.
        if(displayUnits->updated()) {
            displayUnitsFlag = displayUnits->getNewVal();
            LOG1("Display Units has changed to ");
            LOG1(displayUnits->getNewVal() ? "°F!\n" : "°C\n");
        }

        if(coolingThresholdTemperature->updated()) {            
            sendIrCommand(coolingThresholdTemperature->getNewVal());
            if (displayUnits->getNewVal() == CELSIUS) {
                LOG1("coolingThresholdTemperature has changed to %.1f °C!\n", coolingThresholdTemperature->getNewVal<float>());
            }
            else {
                LOG1("coolingThresholdTemperature has changed to %.1f °F!\n", unitCovert(coolingThresholdTemperature->getNewVal<float>()));
            }
        }

        if(swingMode->updated()) {
            sendIrCommand(swingMode->getNewVal() ? SWINGENABLED : SWINGDISABLED);
            LOG1("swingMode has changed to ");
            LOG1(swingMode->getNewVal() ? "ON!\n" : "OFF!\n");
        }

        if (rotationSpeed->updated()) {
            
            // RotationSpeed 1-25 for the auto mode; 26-50 for the low mode
            // 51-75 for the medium mode; 76-100 for the high mode.
            switch ((int)(ceil(rotationSpeed->getNewVal<float>() / 25.0))) {
                case 1:
                    sendIrCommand(ROTATIONAUTO);
                    break;
                case 2:
                    sendIrCommand(ROTATIONLOW);
                    break;
                case 3:
                    sendIrCommand(ROTATIONMEDIUM);
                    break;
                case 4:
                    sendIrCommand(ROTATIONHIGH);
                    break;
                default:
                    // Doing nothing, because when the rotationSpeed = 0,
                    // the homekit will shutdown the cooler by itself.                    
                    break;
            }
            LOG1("rotationSpeed has changed to ");
            LOG1(rotationSpeed->getNewVal<float>());
            LOG1("\n");
        }
        
        return true;
    }

    void loop() override {

        if ((millis() - lastUpdateTemperature) > statusUpdatePeriod_MS) {
            lastUpdateTemperature = millis();
            
            if (isnan(currentTemperature)) {
                temperature->setVal(25.0); 
                LOG0("currentTemperature is unavailable!\n");      
            }
            else {
                temperature->setVal(currentTemperature);
            }
            
            switch (currentCoolerState->getVal()) {
                case IDLE:
                    if (temperature->getVal<float>() > coolingThresholdTemperature->getVal<float>()) {
                        currentCoolerState->setVal(COOLING);
                        LOG1("Set currentCoolerState to COOLING\n");
                    }
                    break;
                
                case COOLING:
                    if (temperature->getVal<float>() <= coolingThresholdTemperature->getVal<float>()) {
                        currentCoolerState->setVal(IDLE);  
                        LOG1("Set currentCoolerState to IDLE\n");
                    }
                    break;
                
                default:
                    LOG0("currentCoolerState is error!\n");
                    break;
            }
        } 
    }

    float unitCovert(float temperatrue) {
        return temperatrue * 9 / 5 + 32;
    }
};

#endif // DEV_COOLER_H