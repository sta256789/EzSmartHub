#ifndef DEV_OLED_H
#define DEV_OLED_H

#ifndef OPENWEATHER_SERVICE_H
bool weatherAvailableFlag = false;
String cityStr = "N/A", stateStr = "N/A", countryStr = "N/A";
String currentWeatherIcon = ")";
String forecastWeatherIcon[8];
String forecastWeekNames[8];
String forecastHours[8];
float forecastPOP[4];
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

#include <initializer_list>
#include <map>
#include <U8g2lib.h>
#include "IconData.h"
#include "WeatherFont.h"
#include "WeatherFont_30x30.h"
#include "NTP_Service.h"
#include "PassiveBuzzer.h"


U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ EZSTARTKIT_IO17, /* data=*/ EZSTARTKIT_IO18);   // ESP32 Thing, HW I2C with pin remapping

#define LOGO_WIDTH 128
#define LOGO_HEIGHT 64

#define SMALL_LOGO_WIDTH 16
#define SMALL_LOGO_HEIGHT 16

enum DisplayMode {
    NORMAL = 0,
    POMODORO = 1 
};

enum PomodoroState {
    RESET = 0,
    READY = 1,
    TASK = 2,
    BREAK = 3,    
};

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

void loadingSceneDisplay (HS_STATUS status) {

    pairedStatus = status;
    
    u8g2.setFont(u8g2_font_8x13B_mf);
    u8g2.clear();

    switch (status) {
        case HS_PAIRING_NEEDED:            
            u8g2.firstPage();
            do {            
                u8g2.drawXBMP(0, 0, LOGO_WIDTH, LOGO_HEIGHT, ScannableTag);
            } while (u8g2.nextPage());
            break;
        
        case HS_PAIRED:
            typingAnimation("Your device has been paired to HomeKit...");
            u8g2.clear();
            break;

        case HS_WIFI_CONNECTING:
            typingAnimation("WiFi connecting...");
            break;
        
        default:
            typingAnimation(homeSpan.statusString(status));
            break;
    }

    LOG1("\nHS_STATUS: %s\n", homeSpan.statusString(status));
}

struct DEV_OLED : Service::Switch {    
        
    const int Task_Period = 1500;
    const int Break_Period = 300;
    const int Rest_Period = 1800;
    const int Max_Finished_Times = 4;

    enum PomodoroState currentPomodoroState;
    enum PomodoroState nextPomodoroState;    

    bool onTaskFlag;
    int statePeriod;
    int timerSecond;    
    int timerMinute;
    int stateProgress; 
    int taskFinishedTimes; 
    
    enum DisplayMode displayMode;
    int maxPage;
    int page;
    
    uint32_t updatePeriod_MS;
    uint32_t time_now;    

    int selectPin;
    int powerPin;

    // reference to the On Characteristic
    SpanCharacteristic *displayState;

    DEV_OLED(int selectPin, int powerPin) : Service::Switch() {

        buzzerInitialize();
        
        currentPomodoroState = RESET;
        nextPomodoroState = TASK;
        statePeriod = Task_Period;
        timerSecond = statePeriod;    
        timerMinute = timerSecond / 60;
        stateProgress = 100 - (timerSecond * 100) / Task_Period;
        taskFinishedTimes = 0;        
        onTaskFlag = false;               

        displayMode = NORMAL;
        maxPage = 3;
        page = 1;

        updatePeriod_MS = 1000;
        time_now = millis();

        this->selectPin = selectPin;
        this->powerPin = powerPin;
        
        displayState = new Characteristic::On(true);

        // Create new SpanButton to control power using pushbutton on pin number "buttonPin"
        new SpanButton(selectPin);
        new SpanButton(powerPin);
        
        // OLED Initialize        
        u8g2.begin();

        LOG0(F("OLED has been initialized!!\n"));
        
    } // end constructor

    boolean update() override {

        LOG1("Current Power=");
        LOG1(displayState->getVal() ? "true\n" : "false\n");        

        if (displayState->updated()) {
            if (!displayState->getNewVal()) {            
                u8g2.clear();
            }        
            else {
                if (page == 0) {
                    page = 1;
                } 
                displayPage();               
            }            
            LOG1("After press button from HomeKit, New Power=");
            LOG1(displayState->getNewVal() ? "true\n" : "false\n");  
            LOG1("\nPage: %d\n", page);          
        }

        return true;
    }

    void button(int buttonPin, int pressType) override {

        LOG1("Found button press on pin: ");
        LOG1(buttonPin);
        LOG1("\ntype: ");
        LOG1(pressType == SpanButton::LONG ? "LONG" : (pressType==SpanButton::SINGLE) ? "SINGLE" : "DOUBLE");
        LOG1("\n");    

        if (buttonPin == selectPin) {

            // If a SINGLE press of the power button...
            if (pressType == SpanButton::SINGLE) {

                if (displayMode == POMODORO) {
                    
                    // Record the currnetState before goto state STOP.
                    // When the button be preesed next time, currentState can resume to the original one. 
                    // if (currentPomodoroState != STOP) {
                    //     tempPomodoroState = currentPomodoroState;
                    // } 
                    currentPomodoroState = nextPomodoroState;
                }
                else {
                    if (page < maxPage) {                    
                        ++page;
                    }
                    else {
                        page = 1;
                    } 

                    // ...toggle the value of the power Characteristic          
                    displayState->setVal(true);
                }

                displayPage();
                LOG1("Mode: %d Page: %d/%d\n", displayMode, page, maxPage);
            } 
            else if (pressType == SpanButton::DOUBLE) {

                if (displayMode == POMODORO) {

                    // Skip the state BREAK or state READY(ready to break) to state READY(ready to start a task)
                    if (!onTaskFlag) {

                        // Set second to 0 to force state READY to update the timer.
                        timerSecond = 0;
                        onTaskFlag = true;
                        currentPomodoroState = READY;
                    }
                }                
            }
            else if (pressType == SpanButton::LONG) {

                if (displayMode == POMODORO) {
                    displayMode = NORMAL;
                    maxPage = 3;
                    page = 1;
                }
                else {
                    displayMode = POMODORO;
                    maxPage = 2;
                    page = 1;
                }
                displayPage();
                LOG1("Mode: %d Page: %d/%d\n", displayMode, page, maxPage);
            }     
        }
        
        if (buttonPin == powerPin) {

            // If a SINGLE press of the power button...
            if (pressType == SpanButton::SINGLE) {
                
                // ...toggle the value of the power Characteristic          
                displayState->setVal(1 - displayState->getVal());
                page = displayState->getVal();  
                displayPage();
            } 
            else if (pressType == SpanButton::LONG) {

                if (displayMode == POMODORO) {

                    // Reset the Pomodoro timer
                    currentPomodoroState = RESET;                    
                    LOG1("Reset the Pomodoro timer!\n");
                }
                else {

                    // Update weather information manually
                    weatherUpdate();
                }
                displayPage();                
            }     
        }
    }

    void loop() {

        while (millis() - time_now > updatePeriod_MS && ntpAvailableFlag && pairedStatus == HS_PAIRED
            && (displayState->getVal() || displayMode == POMODORO)) {

            time_now = millis();

            if (displayMode == POMODORO) {
                switch (currentPomodoroState) {
                    case RESET:
                        statePeriod = Task_Period;
                        timerSecond = statePeriod;
                        timerMinute = timerSecond / 60;
                        stateProgress = 100 - (timerSecond * 100) / statePeriod;                    
                        taskFinishedTimes = 0;
                        onTaskFlag = true;
                        currentPomodoroState = READY;                                                
                        break;
                    
                    case READY:
                        if (onTaskFlag) {
                            if (taskFinishedTimes < 4) {                                 
                                statePeriod = Task_Period;
                                nextPomodoroState = TASK;                               
                            }
                            else {
                                nextPomodoroState = RESET;                                
                            }                             
                        }                        
                        else {
                            if (taskFinishedTimes < 4) {
                                statePeriod = Break_Period;
                            }
                            else {                                
                                statePeriod = Rest_Period;
                            }   
                            nextPomodoroState = BREAK;                         
                        }

                        // If a state is over, reset the timer.
                        // Other conditions(e.g. stop timer or ready to reset) don't reset.
                        if (timerSecond <= 0 && nextPomodoroState != RESET) {
                            timerSecond = statePeriod;
                        }                        
                        timerMinute = timerSecond / 60;
                        stateProgress = 100 - (timerSecond * 100) / statePeriod;
                        break;

                    case TASK:
                        if (timerSecond > 0) {
                            timerSecond -= 1;
                            timerMinute = timerSecond / 60;
                            stateProgress = 100 - (timerSecond * 100) / statePeriod; 
                            nextPomodoroState = READY;                           
                        }
                        else {
                            ++taskFinishedTimes;
                            onTaskFlag = false; 
                            currentPomodoroState = READY;
                            ringBuzzer(taskEndingMelody, taskEndingDuration);                          
                        }
                        break;

                    case BREAK:
                        if (timerSecond > 0) {                    
                            timerSecond -= 1;
                            timerMinute = timerSecond / 60;
                            stateProgress = 100 - (timerSecond * 100) / statePeriod;
                            nextPomodoroState = READY;                                                   
                        }
                        else {
                            onTaskFlag = true;                                                            
                            currentPomodoroState = READY;
                            if (taskFinishedTimes < 4) {
                                ringBuzzer(breakEndingMelody, breakEndingDuration);  
                            }
                            else {
                                ringBuzzer(setCompletedMelody, setCompletedDuration);
                            }                                                   
                        }
                        break;
                    
                    default:
                        LOG0("POMODORO state error!\n");
                        break;
                }
            }
            displayPage();                        
        }
    }

    void displayPage() {
        if (displayMode == NORMAL) {
            switch (page) {
                case 0:
                    u8g2.clear();                
                    break;
                
                case 1:
                    updatePeriod_MS = 1000;                                    
                    u8g2.firstPage();
                    do {
                        displayClock();
                        displayIcon();   
                    } while (u8g2.nextPage());                        
                    break;
    
                case 2:           
                    updatePeriod_MS = 1800000;                         
                    u8g2.firstPage();
                    do {                    
                        displayForecast();
                    } while (u8g2.nextPage());                        
                    break;
    
                case 3:      
                    updatePeriod_MS = 1800000;                              
                    u8g2.firstPage();
                    do {                    
                        displayPOP();
                    } while (u8g2.nextPage());
                    break;               
    
                default:
                    updatePeriod_MS = 10000;                    
                    u8g2.firstPage();
                    do {
                        displayErrorMessage(); 
                    } while (u8g2.nextPage());                    
                    break;
            }
        }
        else {
            switch (page) {
            case 0:
                u8g2.clear();                
                break;
            
            case 1:
                updatePeriod_MS = 1000;                                       
                u8g2.firstPage();
                do {
                    displayPomodoroTimer();
                    displayPomodoroCheckbox();

                    if (currentPomodoroState == READY && onTaskFlag == true && taskFinishedTimes < 4 && timerSecond == statePeriod) {
                        displayHintMessage("Let's start a task!");
                    }
                    else if (currentPomodoroState == READY && onTaskFlag == false && taskFinishedTimes < 4 && timerSecond == statePeriod) {
                        displayHintMessage("Let's take a break!");
                    }
                    else if (currentPomodoroState == READY && onTaskFlag == false && taskFinishedTimes == 4 && timerSecond == statePeriod) {
                        displayHintMessage("Let's take a rest!");
                    }
                    else if (currentPomodoroState == READY && nextPomodoroState == RESET) {
                        displayHintMessage("Congrats! A set is over!");
                    }
                    else {
                        displayPomodoroBar();
                    }                                                       
                } while (u8g2.nextPage());                
                break;
            
            default:
                updatePeriod_MS = 10000;
                u8g2.firstPage();
                do {
                    displayErrorMessage(); 
                } while (u8g2.nextPage());                                
                break;
            }
        }        
    }

    void displayClock() {
        time_t now;
        struct tm timeInfo;

        time(&now);
        localtime_r(&now, &timeInfo);
        
        // Week
        u8g2.setFont(u8g2_font_8x13B_mf);
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
        u8g2.setFont(u8g2_font_8x13B_mf);
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
            u8g2.print(iconMap[currentWeatherIcon]);                
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

    void displayForecast() {
                
        // Print the location
        u8g2.setFont(u8g2_font_5x8_mf);
        int cursorX = 0;
        int cursorY = u8g2.getMaxCharHeight() - 1;
        u8g2.setCursor(0, cursorY);
        u8g2.print(cityStr); 

        cursorY += u8g2.getMaxCharHeight();
        u8g2.setCursor(0, cursorY);
        u8g2.print(stateStr);
        u8g2.print(", ");
        u8g2.print(countryStr);        

        // Print the next four weather icons
        u8g2.setFont(WeatherFont_30x30);
        cursorY += u8g2.getMaxCharHeight();
        int weatherFontWidth = u8g2.getMaxCharWidth();        
        int cursorOffsetX;
        int gap = 2;        
        
        if (!weatherAvailableFlag) {
            
            // if the weatehr information is unavailable, print the symbol N/A. 
            for (int day = 1; day < 5; ++day) {
                u8g2.setCursor(cursorX, cursorY);
                u8g2.print(")");                
                
                u8g2.setFont(u8g2_font_6x13B_mf);
                cursorOffsetX = weatherFontWidth / 2 - u8g2.getStrWidth("N/A") / 2;
                
                // Print the N/A on the last line.
                u8g2.setCursor(cursorX + cursorOffsetX, 63);
                u8g2.print("N/A");

                u8g2.setFont(WeatherFont_30x30);
                cursorX += (u8g2.getMaxCharWidth() + gap);                
            }
        }
        else {
            for (int day = 1; day < 5; ++day) {
                u8g2.setCursor(cursorX, cursorY);
                u8g2.print(iconMap[forecastWeatherIcon[day]]);                
                
                u8g2.setFont(u8g2_font_6x13B_mf);
                cursorOffsetX = weatherFontWidth / 2 - u8g2.getStrWidth(forecastWeekNames[day].c_str()) / 2;
                
                // Print the weekNames on the last line.
                u8g2.setCursor(cursorX + cursorOffsetX, 63);
                u8g2.print(forecastWeekNames[day]);

                u8g2.setFont(WeatherFont_30x30);
                cursorX += (u8g2.getMaxCharWidth() + gap);                
            }  
        }
    }

    void displayPOP() {

        int hLineX = 3;
        int hLneY = 40;
        int hLineLength = 120;

        u8g2.setFont(u8g2_font_7x13B_mf);        
        u8g2.drawStr(0, 12, "POP(%):");

        // Draw a umbrella
        u8g2.setFont(u8g2_font_9x15_m_symbols);
        u8g2.drawGlyph(105, 14, 0x2602);

        // Draw a horizontal line
        u8g2.drawHLine(hLineX, hLneY, hLineLength);

        // Draw the arrow
        u8g2.drawLine(hLineX + hLineLength, hLneY, hLineX + hLineLength - 4, hLneY + 3);
        u8g2.drawLine(hLineX + hLineLength, hLneY, hLineX + hLineLength - 4, hLneY - 3);

        int gap = 45;
        int vLineX = hLineX + 15;
        int vLineY = hLneY - 4;
        int vLineLength = 8;
        String popStr;
        int cursorOffsetX;
        int cursorOffsetY;
        
        u8g2.setFont(u8g2_font_6x13B_mf);

        // Print the POPs
        for (int hour = 1; hour < 4; ++hour) {

            // if the weatehr information is unavailable, print the symbol N/A. 
            if (!weatherAvailableFlag) {                               
                cursorOffsetX = u8g2.getStrWidth("N/A") / 2;
                cursorOffsetY = 6;
                u8g2.setCursor(vLineX + gap * (hour - 1) - cursorOffsetX, vLineY - cursorOffsetY);
                u8g2.print("N/A");
            }
            else {

                // Probability of precipitation. The values of the parameter vary between 0 and 1, 
                // where 0 is equal to 0%, 1 is equal to 100%
                popStr = String((int)(forecastPOP[hour] * 100));
                popStr += "%";
                cursorOffsetX = u8g2.getStrWidth(popStr.c_str()) / 2;
                cursorOffsetY = 6;
                u8g2.setCursor(vLineX + gap * (hour - 1) - cursorOffsetX, vLineY - cursorOffsetY);
                u8g2.print(popStr);
            }
        }
        
        // Draw the dividing lines
        for (int i = 0; i < 3; ++i) {
            u8g2.drawVLine(vLineX + gap * i, vLineY, vLineLength);
        }

        // Print the next 3 hours
        for (int hour = 1; hour < 4; ++hour) { 
            
            // if the weatehr information is unavailable, print the symbol N/A.
            if (!weatherAvailableFlag) {                                
                cursorOffsetX = u8g2.getStrWidth("N/A") / 2;
                cursorOffsetY = u8g2.getMaxCharHeight();

                u8g2.setCursor(vLineX + gap * (hour - 1) - cursorOffsetX, vLineY + vLineLength + cursorOffsetY);
                u8g2.print("N/A");
            }
            else {
                cursorOffsetX = u8g2.getStrWidth(forecastHours[hour].c_str()) / 2;
                cursorOffsetY = u8g2.getMaxCharHeight();

                u8g2.setCursor(vLineX + gap * (hour - 1) - cursorOffsetX, vLineY + vLineLength + cursorOffsetY);
                u8g2.print(forecastHours[hour]);
            }            
        }        
    }

    void displayPomodoroTimer() {        

        u8g2.setFont(u8g2_font_inb24_mn);        
        int timerX = 0;
        int timerY = u8g2.getMaxCharHeight() - 1;
        u8g2.setCursor(timerX, timerY);
        if (timerMinute < 10) {
            u8g2.print("0");      
        }
        u8g2.print(timerMinute);
        u8g2.print(":");
        if (timerSecond % 60 < 10) {
            u8g2.print("0");      
        }
        u8g2.print(timerSecond % 60);        
    }

    void displayPomodoroBar() {
        
        int emptyBarX = 0;
        int emptyBarY = 44;
        int emptyBarWidth = 104;
        int emptyBarHeigh = 20;
        int emptyBarRadius = 2;
        int space = 2;
        int filledBarX = emptyBarX + space;
        int filledBarY = emptyBarY + space;
        int filledBarWidth = stateProgress;
        int filledBarHeigh = emptyBarHeigh - 2 * space;

        // The radius argument of the drawRBox/drawRFrame, must meet the requirement w >= 2 * (r + 1)
        int filledBarRadius = stateProgress / 2 - 1 >= emptyBarRadius ? emptyBarRadius: 0;
                
        String progressStr = String(filledBarWidth);
        progressStr += " %";

        u8g2.setFont(u8g2_font_6x13B_mf);

        // Draw the progress bar and the edge
        u8g2.drawRFrame(emptyBarX, emptyBarY, emptyBarWidth, emptyBarHeigh, emptyBarRadius);
        u8g2.drawRBox(filledBarX, filledBarY, filledBarWidth, filledBarHeigh, filledBarRadius);
        
        // Draw the progress inside the bar
        u8g2.setFontMode(1);
        u8g2.setDrawColor(2);
        u8g2.drawStr(emptyBarX + (emptyBarWidth - u8g2.getStrWidth(progressStr.c_str())) / 2, 
            filledBarY + u8g2.getMaxCharHeight() - 1, progressStr.c_str());
        u8g2.setFontMode(0);
        u8g2.setDrawColor(1);
    }    

    void displayPomodoroCheckbox() {

        u8g2.setFont(u8g2_font_unifont_t_76);
        
        // Set the checkboxes on the rightmost side
        int checkboxX = u8g2.getDisplayWidth() - u8g2.getMaxCharWidth();
        int checkboxY = u8g2.getMaxCharHeight();

        // Draw the filled checkbox 
        for (int i = 0; i < taskFinishedTimes; ++i) {
            u8g2.drawGlyph(checkboxX, checkboxY, 0x2611);
            checkboxY += u8g2.getMaxCharHeight();
        }

        // Draw the empty checkbox                
        for (int i = 0; i < Max_Finished_Times - taskFinishedTimes; ++i) {
            u8g2.drawGlyph(checkboxX, checkboxY, 0x2610);
            checkboxY += u8g2.getMaxCharHeight();
        }     
    }

    void displayHintMessage(string hintMessage) {

        u8g2.setFont(u8g2_font_5x8_mf);

        int space = 2;
        int gap = 1;
        
        // Set the dialog box background on the bottom which can contain tree row and plus a space on top/botton sides
        int rBoxWidth = u8g2.getDisplayWidth();
        int rBoxHeigh = u8g2.getMaxCharHeight() * 3 + 2 * space;
        int rBoxX = 0;
        int rBoxY = u8g2.getDisplayHeight() - rBoxHeigh;
        int radius = 7;

        u8g2.drawRBox(rBoxX, rBoxY, rBoxWidth, rBoxHeigh, radius);

        // Set the dialog box edge with a gap between the background
        int rFrameX = rBoxX + gap;
        int rFrameY = rBoxY + gap;
        int rFrameWidth = rBoxWidth - 2 * gap;
        int rFrameHeigh = rBoxHeigh - 2 * gap;    
        
        u8g2.setDrawColor(0);
        u8g2.drawRFrame(rFrameX, rFrameY, rFrameWidth, rFrameHeigh, radius);

        // Center the first sentence
        int hintX = (u8g2.getDisplayWidth() - u8g2.getStrWidth(hintMessage.c_str())) / 2;
        int hintY = rBoxY + gap + u8g2.getMaxCharHeight();
        
        u8g2.drawStr(hintX, hintY, hintMessage.c_str());

        // Second sentence is flush left
        hintMessage = "Press button A";
        hintX = rFrameX + 2 * gap;
        hintY += u8g2.getMaxCharHeight();
        u8g2.drawStr(hintX, hintY, hintMessage.c_str());

        // Third sentence is flush right
        hintMessage = "to continue...";
        hintX = rFrameX + rFrameWidth - 4 * gap - u8g2.getStrWidth(hintMessage.c_str());
        hintY += u8g2.getMaxCharHeight();
        u8g2.drawStr(hintX, hintY, hintMessage.c_str());        
        u8g2.setDrawColor(1);
        
    }

    void displayErrorMessage() {        
        u8g2.setFont(u8g2_font_8x13B_mf);
        typingAnimation("THIS IS AN ERROR!");        
    } 
};

#endif // DEV_OLED_H