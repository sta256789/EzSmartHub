#ifndef DEV_RELAY_H
#define DEV_RELAY_H

struct DEV_Relay : Service::Switch {         
    
    // This variable stores the pin number defined for this relay
    int relayPin;
    
    // Reference to the On Characteristic
    SpanCharacteristic *power;                        
    
    DEV_Relay(int relayPin, int powerPin = -1) : Service::Switch() {
        
        // Save power pushbutton pin number
        power = new Characteristic::On(); 
        
        // If the powerPin is assigned, then create an instance of a reality button.
        if (powerPin != -1) {
            new SpanButton(powerPin);
        }        
        
        // Don't forget to store relayPin...
        this->relayPin = relayPin; 
        
        // ...and set the mode for relayPin to be an OUTPUT (standard Arduino function)
        pinMode(relayPin, OUTPUT);                             
      
    }
  
    boolean update() {                              
  
        LOG1("Updating relay on pin = ");
        LOG1(relayPin);
        LOG1("\n");
        LOG1("Current Power = ");
        LOG1(power->getVal()?"true":"false");
        LOG1("\n");    

        if(power->updated()) {
            LOG1("New Power = ");
            LOG1(power->getNewVal() ? "true" : "false");
            LOG1("\n");
        } 
        
        // Use a standard Arduino function to turn on/off relayPin 
        // based on the return of a call to power->getNewVal()
        digitalWrite(relayPin, power->getNewVal());            
        
        return(true);
    }
  
    // Here is the button() method where all the PushButton actions are defined.
    // Take note of the signature, and use of the word "override".
    void button(int powerPin, int pressType) override {
  
        LOG1("Found button press on pin: ");            
        LOG1(powerPin);
        LOG1("\ntype: ");
        LOG1(pressType == SpanButton::LONG ? "LONG" : (pressType==SpanButton::SINGLE) ? "SINGLE" : "DOUBLE");
        LOG1("\n");    

        if (powerPin == powerPin) {

            // If a SINGLE press of the power button...
            if (pressType == SpanButton::SINGLE) {

                // ...toggle the value of the power Characteristic            
                power->setVal(1 - power->getVal());
                digitalWrite(relayPin, power->getNewVal());
            }      
        }
    }
};

#endif // DEV_RELAY_H