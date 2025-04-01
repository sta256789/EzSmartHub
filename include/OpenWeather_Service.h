#ifndef OPENWEATHER_SERVICE_H
#define OPENWEATHER_SERVICE_H

#include <OpenWeatherOneCall.h>
#include "NTP_Service.h"

#define MAXAPICALLSPERDAY 1000

bool weatherAvailableFlag = false;

String weatherIcon = "01d";

int updateTimes = 0;

char ONECALLKEY[] = "";

//*************** LOCATION ************************

int myTimeZone = 8;  //<--------- GMT OFFSET

//Location MODES are used to tell the program how you are delivering your coordinates:
// 1 LAT/LON  <----- Can be from GPS, manual as below, or whatever method gets you a latitude and longitude except IP location
// 2 CITYID   <----- From OpenWeatherMap City ID list. Not very accurate.
// 3 IP ADDRESS [NOT REALLY SUGGESTED CAN BE WILDLY OFFSET LOCATION IF HOTSPOT]

int locationMode = 3;

//For Latitude and Longitude Location MODE 1 setting if used
float myLATITUDE;  //<-----This is Toms River, NJ
float myLONGITUDE;

//For City ID Location MODE setting if used
int myCITYID;  //<-----Toms River, NJ USA

//*************** END LOCATION **********************

//*************** FLAGS *****************************
int myCURRENT = 1;                      //<-----0 is CURRENT off, 1 is on
int myAIRQUALITY = 1;                   //<-----0 is Air Quality off, 1 is on
int myTIMESTAMP = 1;                    //<-----0 is TIMESTAMP off, 1 is TIMESTAMP on
char timestampDate[11] = "04/01/2025";  //<-----MM/DD/YYYY right here limit is 4 days in future, past is 01/01/1979
int myOVERVIEW = 1;                     //<-----0 is OVERVIEW off, 1 is OVERVIEW on
char overviewDate[9] = "TOMORROW";      //<-----"TODAY" or "TOMORROW"
//***************************************************

//************** EXCLUDES ***************************
// Excludes are EXCL_D, EXCL_H, EXCL_M, EXCL_A
// Those are DAILY, HOURLY, MINUTELY, and ALERTS
// You set them like this: myEXCLUDES = EXCL_D+EXCL_H+EXCL_M+EXCL_A
// If you leave them set to 0 as below you get a JSON file with ALL CURRENT WEATHER measurements which is a huge file

int myEXCLUDES = 0;  //<-----0 Excludes is default
//***************************************************

//*************** UNITS OF MEASURMENT and DATE TIME FORMAT ***************

int myUNITS = METRIC;  //<-----METRIC, IMPERIAL, KELVIN (IMPERIAL is default)

//Date Time Format
int myDTF = 2;     /*
                     1 M/D/Y 24H
                     2 D/M/Y 24H
                     3 M/D/Y 12H
                     4 D/M/Y 12H
                     5/6 TIME ONLY 24H
                     7/8 TIME ONLY 12H
                     9 DAY SHORTNAME
                     10 M/D/Y ONLY, 
                     11 D/M/Y ONLY
                     
                     ISO8601 options: 
                     12 YYYY-MM-DD ONLY, 
                     13 THH:MM:SS ONLY
                     14 YYYY-MM-DDTHH:MM:SSY 24H 
                     */
//************************************************************************



OpenWeatherOneCall OWOC;  // <------ Invoke Library like this

void weatherUpdate(int num = 0) {

    //Now call the weather. Please notice no arguments are required in this call
    if (updateTimes < MAXAPICALLSPERDAY) {
        OWOC.parseWeather();
    }
    else {
        LOG0("\nThe free api calls have run out!\n");
    }

    // Location info is available for ALL modes
    LOG0("\nLocation: % s, % s % s\n", OWOC.location.CITY, OWOC.location.STATE, OWOC.location.COUNTRY);
    
    //Check if data is in the struct for all variables before using them
    if (OWOC.current) {
        ++updateTimes;
        ntpAvailableFlag = true;
        weatherAvailableFlag = true;
        weatherIcon = OWOC.current->icon;
        LOG0("\nCURRENT\n");
        LOG0("Temp : % .0f\n", OWOC.current->temperature);
        LOG0("Humidity : % .0f\n", OWOC.current->humidity); 
        LOG0("Weather id: : % .0f\n", OWOC.current->id);        
        LOG0("Weather main: : %s\n", OWOC.current->main);
        LOG0("Weather summary: : %s\n", OWOC.current->summary);
        LOG0("Weather icon: : %s\n", OWOC.current->icon);        
        LOG0("\nWeather update times: %d\n", updateTimes);           
    } 
    else {
        clockUpdate();
        weatherAvailableFlag = false;
        LOG0("\nThe weather information is unavailable!\n");
        LOG0("\nCURRENT IS OFF or EMPTY\n");
    }
}

#endif // OPENWEATHER_SERVICE_H