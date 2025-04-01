#ifndef DEV_OLED_H
#define DEV_OLED_H

#ifndef OPENWEATHER_SERVICE_H
bool weatherAvailableFlag = false;
String weatherIcon = "01d";
#endif

#ifndef DEV_DHT_SENSOR_H
bool dhtTemperatureFlag = false;
bool dhtHumidityFlag = false;
float currentTemperature = 0.0;
float currentHumidity = 0.0;
#endif

#ifndef DEV_COOLER_H
bool displayUnitsFlag = false;
#endif

#include <map>
#include <U8g2lib.h>
#include "IconData.h"
#include "WeatherFont.h"
#include "NTP_Service.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ EZSTARTKIT_IO17, /* data=*/ EZSTARTKIT_IO18);   // ESP32 Thing, HW I2C with pin remapping

#define LOGO_WIDTH 128
#define LOGO_HEIGHT 64

#define SMALL_LOGO_WIDTH 16
#define SMALL_LOGO_HEIGHT 16

HS_STATUS pairedStatus;

std::map<String, char> iconMap {
    {"01d", 'B'}, {"02d", 'H'}, {"03d", 'N'}, {"04d", 'Y'}, {"09d", 'R'}, {"10d", 'Q'},
    {"11d", 'P'}, {"13d", 'W'}, {"50d", 'J'}, {"01n", 'C'}, {"02n", 'I'}, {"03n", '5'},
    {"04n", '%'}, {"09n", '8'}, {"10n", '7'}, {"11n", '6'}, {"13n", '#'}, {"50n", 'K'}, 
};

string spacesAdding(string content, int maxCharPerRow) {  

    bool completedFlag;
    int lastSpaceIndex;
    string displayContent;

    if (content.length() <= maxCharPerRow) {            
        return content;
    }
    else {
        
        completedFlag = false;
        lastSpaceIndex = -1;

        for (int index = 0; index < content.length() && completedFlag == false; ++index) {
            
            // Record the index of the last space
            if (content.compare(index, 1, " ") == 0) {
                lastSpaceIndex = index;                                   
            }
            
            // Check the last character pre row
            if ((index + 1) % maxCharPerRow == 0) {

                // Don't do anything. Just ignore the space at the head of the remaining contents and save it.
                if (content.compare(index, 1, " ") != 0 && content.compare(index + 1, 1, " ") == 0
                    || content.compare(index, 1, " ") == 0) {

                    displayContent = content.substr(0, maxCharPerRow);
                    
                    // Save the remaining contents starting from the last space for the iteration.

                    // The first character of the remainding contents is not a space.
                    if (content.substr(index + 1, 1).compare(" ")) {                            
                        content = content.substr(index + 1);
                    }
                    // If the first character of the remainding contents is space, igonre it (index + 2).
                    else {
                        if (index + 2 < content.length()) {
                            content = content.substr(index + 2);
                        }
                        else {
                            content = "";
                        }
                    }
                    completedFlag = true;
                }
                // Adding space...
                else {
                    
                    // Save the contents to the last space
                    displayContent = content.substr(0, lastSpaceIndex + 1);
                    
                    // Add the spaces to fill the rest of the row
                    for (int space = 0; space < index - lastSpaceIndex; ++space) {
                        displayContent += " ";
                    }
                    
                    // Save the remaining contents starting from the last space for the iteration.
                    content = content.substr(lastSpaceIndex + 1);
                     
                    completedFlag = true;
                }
            }        
        }
        
        return lastSpaceIndex == -1 ? "" : displayContent + spacesAdding(content, maxCharPerRow);
    }
}

// Only monospace fonts are permitted; otherwise, it may casue errors.
void typingAnimation (string content = "This is a demo message: The compare() function in C++ is used to text...", 
    uint32_t tpyingDelay_MS = 50) {

    if (u8g2.getStrWidth(content.c_str()) > u8g2.getDisplayWidth() * (u8g2.getDisplayHeight() / u8g2.getMaxCharHeight())) {
        LOG0("StrWidth: %d\n", u8g2.getStrWidth(content.c_str()));
        LOG0("Total display size: %d\n", u8g2.getDisplayWidth() * (u8g2.getDisplayHeight() / u8g2.getMaxCharHeight()));
        LOG0("The string is out of the range of the display! Using the smaller font or shorten the string to fix it.\n");
        return;
    }
    
    uint32_t time_now = millis();

    int origin_Y = u8g2.getMaxCharHeight() - 1;  
    
    int maxCharPerRow = u8g2.getDisplayWidth() / u8g2.getMaxCharWidth();    

    int maxRow = u8g2.getDisplayHeight() / u8g2.getMaxCharHeight();
           
    int completedRow = 0;

    string displayContent = spacesAdding(content, maxCharPerRow);    
    
    if (displayContent.empty()) {        
        LOG0("There is no space to divide the contents!");
        return;
    }
    
    for (int index = 0; index < displayContent.length() + 1; ++index) { 

        // origin place + current row
        int curserPosition_Y = origin_Y + completedRow * u8g2.getMaxCharHeight();
        
        // ignore space
        if (displayContent.compare(index, 1, " ") != 0) {
            while (millis() - time_now < tpyingDelay_MS);    
            
            u8g2.firstPage();
            do { 
                
                // Start to draw the completed row, when it typed an completed row
                for (int row = 0; row < completedRow; ++row) {
                    u8g2.drawStr(0, origin_Y + row * u8g2.getMaxCharHeight(), displayContent.substr(maxCharPerRow * row, maxCharPerRow).c_str());
                }
                
                // Typing
                u8g2.drawStr(0, curserPosition_Y, displayContent.substr(maxCharPerRow * completedRow, index % maxCharPerRow).c_str());
                
            } while (u8g2.nextPage());
        }

        time_now = millis();

        // index + 1 is the current amount of characters, 
        // so (index + 1) % maxCharPerRow == 0 means a row had been drawn completely  
        if ((index + 1) % maxCharPerRow == 0) {
            completedRow += 1;                            
        }
        
    }

    // completedRow == 0 -> 0 completed row + index
    // (0, index)
    //
    // completedRow == 1 -> 1 completed row + index, but start from maxCharPerRow
    // (0, maxCharPerRow)                    
    // (maxCharPerRow * 1, index)
    // 
    // completedRow == 2 -> 2 completed row + index, but start from maxCharPerRow * 2                   
    // (0, maxCharPerRow)
    // (maxCharPerRow * 1, maxCharPerRow)                    
    // (maxCharPerRow * 2, index)
    //  
    // and so on...    
}

void qrCodeDisplay (HS_STATUS status) {

    uint32_t clearDelay_MS = 3000;
    uint32_t time_now = millis(); 
    
    u8g2.setFont(u8g2_font_8x13B_tf);
    u8g2.clear();

    if (status == HS_PAIRING_NEEDED) {        
        u8g2.firstPage();
        do {            
            u8g2.drawXBMP(0, 0, LOGO_WIDTH, LOGO_HEIGHT, ScannableTag);
        } while (u8g2.nextPage());
        pairedStatus = status;
        LOG0("\n***** DEVICE NOT YET PAIRED -- PLEASE PAIR WITH HOMEKIT APP *****\n");
    }    
    else if (status == HS_PAIRED) {
        typingAnimation("Your device has been paired to HomeKit...");
        pairedStatus = status;
        LOG0("\n***** YOUR DEVICE HAS BEEN PAIRED TO HOMEKIT...!! *****\n");
        while (millis() - time_now < clearDelay_MS);
        u8g2.clear();
    }
    else {
        u8g2.clear();
    }    
}

struct DEV_OLED : Service::Switch {

    // Set the clock delay
    uint32_t clockDelay_MS = 1000;
    uint32_t time_now = millis();

    // reference to the On Characteristic
    SpanCharacteristic *displayState;

    DEV_OLED(int powerPin) : Service::Switch() {
        
        displayState = new Characteristic::On(true);

        // Create new SpanButton to control power using pushbutton on pin number "buttonPin"
        new SpanButton(powerPin);
        
        // OLED Initialize
        u8g2.begin();

        LOG0(F("\n***** OLED HAS BEEN INITIALIZED!! *****\n"));
        
    } // end constructor

    boolean update() override {

        LOG1("Current Power=");
        LOG1(displayState->getVal() ? "true\n" : "false\n");        

        if (displayState->updated()) {
            if (!displayState->getNewVal()) {            
                u8g2.clear();
            }        
            LOG1("After press button from HomeKit, New Power=");
            LOG1(displayState->getNewVal() ? "true\n" : "false\n");            
        }

        return true;
    }

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
                displayState->setVal(!displayState->getVal());
                if (!displayState->getVal()) {            
                    u8g2.clear();
                }           
            }      
        }          
    }

    void loop() {

        while (millis() - time_now > clockDelay_MS && displayState->getVal() && ntpAvailableFlag && pairedStatus == HS_PAIRED) {
            time_now = millis();

            u8g2.firstPage();
            do {
                displayClock();
                displayIcon();   
            } while (u8g2.nextPage());            
        }
    }

    void displayClock() {
        time_t now;
        struct tm timeInfo;

        time(&now);
        localtime_r(&now, &timeInfo);
        
        // Week
        u8g2.setFont(u8g2_font_8x13B_tf);
        u8g2.setCursor(2, 12);
        u8g2.print(&timeInfo, "%a");

        // Year
        u8g2.setCursor(40, 12);
        u8g2.print(&timeInfo, "%Y");            
    
        
        // Hour & Minute
        u8g2.setFont(u8g2_font_inr16_mn);
        u8g2.setCursor(0, 34);
        u8g2.print(&timeInfo, "%R");

        // Second
        u8g2.setFont(u8g2_font_6x10_tn);
        u8g2.setCursor(66, 34);
        u8g2.print(&timeInfo, "%S");


        // Month        
        u8g2.setFont(u8g2_font_8x13B_tf);
        char strftime_buf[4];
        strftime(strftime_buf, sizeof(strftime_buf), "%b", &timeInfo);      
        u8g2.drawButtonUTF8(2, 52, U8G2_BTN_INV, 0,  2,  2, strftime_buf);

        // Day
        
        u8g2.setFont(u8g2_font_bubble_tn);
        
        // The place of the original cursor is (30, 62).
        // When the string of day(e.g. 28) which has maximun width, 
        // the cursor do not need to change. => (maxDayStrWidth - dayStrWidth) = 0
        // To center the string => divide (maxDayStrWidth - dayStrWidth) by 2
        strftime(strftime_buf, sizeof(strftime_buf), "%d", &timeInfo);
        int dayStrWidth = u8g2.getStrWidth(strftime_buf);        
        int maxDayStrWidth = u8g2.getStrWidth("28");
        int cursorOffset = (maxDayStrWidth - dayStrWidth) / 2;
        
        u8g2.setCursor(30 + cursorOffset, 62);        
        u8g2.print(&timeInfo, "%d");
               
    }

    void displayIcon() {

        // Weather icon
        u8g2.setFont(WeatherFont);
        u8g2.setCursor(84, 34);
        if (!weatherAvailableFlag) {            
            // if the weatehr information is unavailable, print the symbol N/A.            
            u8g2.print(")");
        }
        else {
            u8g2.print(iconMap[weatherIcon]);                
        }
        
        // Temperaturee icon
        u8g2.setFont(u8g2_font_6x12_t_symbols);
        u8g2.drawXBMP(74, 36, SMALL_LOGO_WIDTH, SMALL_LOGO_HEIGHT, logo_bmp_temperature);
        u8g2.setCursor(90, 48);
        if (!dhtTemperatureFlag) {
            u8g2.print("N/A");
        }
        else {            
            u8g2.print(displayUnitsFlag ? unitCovert(currentTemperature) : currentTemperature, 1);
            u8g2.drawGlyph(120, 48, displayUnitsFlag ? 0x2109 : 0x2103);
        }  

        // Humidity icon
        u8g2.drawXBMP(74, 50, SMALL_LOGO_WIDTH, SMALL_LOGO_HEIGHT, logo_bmp_humidity);        
        u8g2.setCursor(90, 62);
        if (!dhtHumidityFlag) {
            u8g2.print("N/A");            
        }
        else {
            u8g2.print(currentHumidity, 1);
            u8g2.print(" %");
        }
        
    }

    float unitCovert(float temperatrue) {
        return temperatrue * 9 / 5 + 32;
    }
    
};

#endif // DEV_OLED_H