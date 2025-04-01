#ifndef COOLERDATA_H
#define COOLERDATA_H

enum AcFunctions {
    POWEROFF = 0,
    POWERON,  
    SWINGDISABLED,
    SWINGENABLED,
    ROTATIONLOW,
    ROTATIONMEDIUM,
    ROTATIONHIGH,
    ROTATIONAUTO,
    TEMPERTURE16 = 16,
    TEMPERTURE17,
    TEMPERTURE18,
    TEMPERTURE19,
    TEMPERTURE20,
    TEMPERTURE21,
    TEMPERTURE22,
    TEMPERTURE23,
    TEMPERTURE24,
    TEMPERTURE25,
    TEMPERTURE26,
    TEMPERTURE27,
    TEMPERTURE28,
    TEMPERTURE29,
    TEMPERTURE30,
    TEMPERTURE31
};

static const char* commandName[] PROGMEM = {
    "POWER OFF",
    "POWER ON",  
    "SWING DISABLED",
    "SWING ENABLED",
    "ROTATION LOW",
    "ROTATION MEDIUM",
    "ROTATION HIGH",
    "ROTATION AUTO",
    "TEMPERTURE 16",
    "TEMPERTURE 17",
    "TEMPERTURE 18",
    "TEMPERTURE 19",
    "TEMPERTURE 20",
    "TEMPERTURE 21",
    "TEMPERTURE 22",
    "TEMPERTURE 23",
    "TEMPERTURE 24",
    "TEMPERTURE 25",
    "TEMPERTURE 26",
    "TEMPERTURE 27",
    "TEMPERTURE 28",
    "TEMPERTURE 29",
    "TEMPERTURE 30",
    "TEMPERTURE 31"
};

static const uint16_t rawIrData[][227] PROGMEM = {
    {3330,1820, 430,1270, 430,1320, 380,570, 330,520, 380,520, 430,1320, 380,570, 330,570, 380,1320, 380,1370, 430,520, 330,1320, 430,520, 380,570, 330,1370, 380,1320, 430,520, 380,1320, 380,1370, 380,570, 330,570, 330,1370, 380,520, 380,570, 330,1370, 380,570, 330,520, 380,520, 380,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,520, 380,570, 330,1370, 380,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,1320, 380,570, 330,570, 380,520, 380,520, 380,520, 380,1320, 430,520, 380,520, 380,520, 380,570, 330,520, 380,570, 330,1370, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 430,470, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,1320, 380},
    {3380,1770, 380,1320, 430,1320, 380,570, 330,570, 380,520, 330,1370, 380,520, 430,520, 380,1320, 380,1370, 380,570, 330,1370, 380,570, 330,570, 330,1370, 380,1370, 380,520, 380,1320, 430,1320, 380,520, 380,570, 330,1370, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,520, 380,570, 380,520, 330,570, 330,570, 380,520, 380,570, 330,520, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,520, 380,1370, 380,570, 330,570, 330,520, 380,570, 380,470, 430,1320, 380,520, 380,570, 380,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,570, 330,570, 330,570, 330,520, 380,520, 380,520, 380,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,470, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,470, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,1320, 430,470, 430,520, 380,520, 380,520, 380,1370, 380},
    {3330,1770, 380,1370, 380,1370, 330,570, 380,520, 380,520, 380,1370, 380,470, 430,520, 380,1370, 380,1370, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 330,1420, 330,570, 330,570, 380,1320, 380,570, 330,570, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,1420, 330,520, 380,570, 330,570, 380,1320, 380,570, 380,520, 380,1370, 330,570, 380,520, 380,1370, 380,1320, 380,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,1420, 330,520, 380,1370, 380,520, 380,520, 430,520, 330,570, 380,520, 380,520, 380,570, 330,570, 330,1370, 380,1370, 380,520, 380,520, 380,520, 430,520, 330,570, 330,570, 380,520, 380,520, 380,570, 330,520, 380,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,570, 330,570, 380,520, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 380,520, 330,570, 330,570, 380,520, 380,520, 380,570, 330,520, 430,520, 330,570, 380,520, 380,1370, 330,570, 380,520, 380,1370, 330,1370, 380,570, 330,570, 380,1370, 330},
    {3430,1670, 430,1320, 380,1370, 380,520, 380,520, 430,470, 430,1320, 430,470, 430,520, 380,1320, 430,1320, 380,520, 430,1320, 380,520, 430,520, 380,1320, 430,1320, 380,520, 430,1320, 380,1370, 380,520, 380,520, 380,1370, 380,570, 330,520, 430,1320, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,470, 430,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,570, 380,1320, 380,520, 380,570, 330,1370, 430,1320, 380,520, 380,570, 380,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,1370, 380,520, 380,570, 330,520, 380,570, 330,520, 430,520, 380,520, 380,520, 380,1370, 380,1320, 430,1320, 430,520, 330,570, 330,570, 380,570, 330,570, 330,570, 330,570, 330,520, 380,570, 330,570, 330,620, 330,570, 330,520, 380,570, 330,570, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 380,520, 330,570, 380,570, 330,570, 330,570, 330,520, 380,570, 380,520, 380,520, 380,520, 380,570, 330,1370, 380,520, 380,570, 330,1370, 380,1370, 380,1320, 430,570, 330,1320, 430},
    {3330,1820, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,1320, 430,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,1320, 430,520, 380,1320, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,470, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,1320, 430,1320, 380,520, 430,1320, 380,1370, 380,520, 380,520, 380,1370, 380},
    {3330,1820, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,1320, 430,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,1320, 430,520, 380,1320, 380,520, 430,520, 380,520, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,1320, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,1320, 430,1320, 380,1370, 380,520, 380,520, 380,1370, 380},
    {3330,1820, 430,1320, 430,1270, 380,520, 480,470, 430,470, 330,1420, 380,520, 380,520, 430,1320, 380,1370, 380,520, 330,1420, 330,570, 330,570, 330,1420, 430,1270, 430,520, 330,1370, 430,1320, 480,420, 480,470, 330,1370, 380,520, 380,570, 330,1370, 480,470, 380,520, 330,570, 330,570, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,570, 330,1370, 380,520, 430,520, 380,1320, 380,570, 330,570, 330,1420, 380,1320, 380,570, 380,520, 330,570, 330,570, 330,570, 380,520, 380,1370, 380,520, 380,1370, 380,520, 380,520, 380,520, 380,570, 380,520, 380,1320, 430,520, 330,1370, 430,1320, 380,1370, 380,520, 380,520, 380,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 380,520, 380,520, 330,570, 380,520, 380,520, 380,520, 380,570, 380,520, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,1370, 380,1370, 380,1320, 430,1320, 380,520, 430,520, 380,1320, 430},
    {3380,1770, 380,1370, 380,1370, 380,520, 380,520, 380,520, 430,1320, 380,520, 380,570, 380,1320, 430,1320, 380,520, 380,1370, 380,520, 380,520, 430,1320, 380,1370, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,520, 430,470, 430,520, 380,520, 380,1370, 380,520, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,1370, 380,1320, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,1370, 380},
    {3430,1670, 480,1270, 480,1270, 480,470, 430,420, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,520, 330,570, 380,1370, 380,1320, 380,570, 380,1320, 380,1370, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 430,470, 430,1320, 380,520, 430,470, 430,470, 430,1320, 380,520, 430,470, 430,1320, 380,520, 380,520, 430,1320, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,1320, 380,1370, 380,1320, 430,1320, 430,470, 430,470, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 430,470, 380,520, 380,520, 380,520, 380,1370, 380,1370, 330,570, 330,1420, 330,570, 330,570, 330,570, 330,1420, 330},
    {3330,1820, 330,1370, 380,1370, 380,520, 380,520, 380,520, 380,1370, 430,470, 380,520, 380,1370, 480,1270, 430,470, 430,1320, 380,520, 380,520, 430,1320, 380,1320, 430,520, 380,1320, 430,1320, 430,470, 430,470, 430,1320, 430,470, 430,470, 430,1320, 430,470, 430,470, 430,470, 430,470, 430,470, 430,470, 430,520, 330,570, 330,570, 330,570, 380,520, 330,570, 380,520, 430,1320, 330,570, 380,520, 380,520, 380,1370, 330,570, 380,520, 380,1370, 330,570, 380,520, 380,1370, 330,1420, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,1370, 380,1370, 330,1370, 380,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 430,470, 330,570, 330,570, 430,470, 430,470, 430,470, 380,520, 430,470, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 430,470, 430,520, 380,520, 380,520, 380,1370, 380,520, 380,1320, 380,520, 430,520, 380,520, 330,1370, 380},
    {3330,1820, 380,1320, 430,1320, 380,520, 380,570, 330,520, 380,1370, 380,520, 380,570, 330,1370, 380,1370, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1320, 430,520, 380,1320, 380,1370, 380,520, 380,520, 480,1270, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,420, 480,1270, 480,470, 430,470, 430,1270, 430,470, 480,420, 480,1270, 480,1270, 430,470, 430,470, 430,470, 380,520, 380,520, 380,570, 330,1370, 380,520, 480,1270, 380,1320, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 380,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,520, 330,570, 330,570, 330,1420, 380},
    {3330,1820, 380,1320, 430,1320, 380,570, 330,570, 380,520, 380,1320, 380,570, 380,520, 380,1320, 380,1370, 380,570, 330,1370, 380,570, 330,520, 380,1370, 380,1320, 430,520, 380,1320, 430,1320, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,520, 380,520, 380,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,520, 380,1370, 380,570, 330,520, 380,1370, 380,1370, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,1370, 380,1370, 380,570, 330,520, 380,570, 330,570, 330,570, 380,520, 330,570, 330,570, 380,520, 380,570, 330,570, 330,570, 330,520, 380,570, 330,520, 380,520, 430,520, 380,520, 330,570, 380,570, 330,570, 330,570, 330,570, 330,570, 330,520, 380,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 480,420, 480,1270, 480,420, 480,420, 480,420, 480,1270, 480},
    {3330,1770, 430,1320, 380,1370, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,1370, 380,520, 380,1320, 430,520, 380,520, 380,1320, 430,1320, 380,570, 380,1320, 480,1270, 380,570, 380,520, 330,1370, 430,470, 380,570, 430,1270, 380,520, 380,570, 380,520, 330,570, 330,570, 430,470, 330,570, 430,470, 380,520, 380,520, 380,520, 380,520, 380,570, 330,1370, 430,470, 380,570, 330,570, 330,1370, 380,520, 380,570, 330,1370, 380,520, 380,570, 330,1370, 380,1320, 430,470, 430,520, 380,520, 380,520, 430,470, 380,570, 330,1370, 380,1320, 430,520, 380,1320, 380,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,520, 380,570, 330,570, 380,470, 430,520, 380,520, 430,470, 430,520, 330,520, 480,470, 330,570, 430,470, 330,570, 380,470, 430,520, 380,520, 380,520, 380,520, 380,570, 330,570, 430,470, 330,570, 330,570, 330,570, 430,420, 430,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 430,470, 380,1320, 380,1370, 380,1370, 430,470, 380,570, 330,570, 330,570, 330,1370, 380},
    {3280,1820, 380,1370, 380,1370, 330,570, 380,520, 380,520, 380,1370, 330,570, 380,520, 380,1370, 330,1370, 380,570, 330,1370, 380,520, 380,520, 380,1370, 380,1370, 380,520, 380,1370, 380,1370, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,1370, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,1320, 380,570, 330,1370, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,1320, 430,1370, 380,520, 380,520, 380,520, 380,570, 330,1370, 380},
    {3480,1670, 380,1370, 380,1320, 480,420, 480,470, 430,470, 430,1270, 480,470, 430,470, 430,1270, 480,1270, 480,420, 480,1270, 480,420, 480,420, 480,1270, 480,1270, 430,470, 430,1320, 430,1270, 480,420, 480,420, 480,1270, 480,420, 480,470, 430,1270, 480,420, 480,420, 430,520, 430,470, 430,470, 380,520, 430,470, 480,420, 380,520, 380,520, 480,470, 330,570, 330,570, 380,1320, 380,520, 380,520, 430,520, 380,1320, 380,520, 430,470, 430,1320, 380,520, 380,520, 430,1320, 380,1370, 380,520, 380,520, 380,520, 380,520, 380,570, 380,520, 380,1320, 380,520, 430,470, 430,1320, 380,520, 380,520, 430,470, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,1370, 380,520, 380,1370, 380,520, 380,520, 430,470, 430,470, 380,1370, 430},
    {3330,1770, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1370, 330,570, 330,1370, 380,520, 380,570, 330,1370, 380,1370, 380,520, 380,1370, 380,1320, 380,570, 330,570, 380,1270, 430,570, 330,570, 380,1270, 430,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,520, 380,520, 380,1370, 380,520, 380,520, 380,520, 430,1320, 380,520, 380,520, 380,1370, 380,520, 330,570, 330,1320, 380,1370, 380,570, 330,570, 430,470, 330,570, 380,570, 330,570, 330,570, 330,520, 380,570, 330,1320, 430,520, 380,520, 380,570, 330,570, 430,470, 330,570, 330,570, 330,570, 330,520, 430,520, 380,520, 380,520, 380,570, 330,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 330,570, 380,570, 330,570, 330,570, 330,570, 330,570, 330,520, 430,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 430,520, 380,520, 380,520, 380,520, 380,1370, 380,520, 430,470, 480,420, 480,420, 480,1270, 430},
    {3380,1770, 430,1320, 380,1370, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,1370, 380,570, 330,1320, 430,520, 380,520, 380,1320, 430,1320, 380,570, 380,1320, 380,1370, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,570, 330,570, 330,1370, 380,1320, 430,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,1370, 380,1320, 430,1320, 380,570, 330,570, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 330,570, 380,520, 330,620, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 330,570, 330,570, 380,570, 330,570, 330,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,1320, 380,1370, 380,570, 330,570, 330,570, 330,570, 380,470, 430,1320, 380},
    {3330,1770, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1320, 380,570, 330,1370, 380,570, 330,570, 330,1370, 380,1370, 380,520, 380,1370, 380,1370, 330,570, 380,520, 380,1370, 330,570, 330,570, 380,1370, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,1370, 330,570, 330,570, 380,520, 380,1370, 330,570, 330,570, 380,1320, 380,570, 330,570, 380,1370, 330,1370, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,1370, 330,1370, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,1370, 330,570, 330,570, 380,520, 380,520, 380,520, 380,1370, 380},
    {3330,1770, 380,1370, 380,1370, 380,520, 380,520, 380,520, 380,1370, 380,520, 380,520, 380,1370, 380,1320, 380,570, 380,1320, 380,570, 330,570, 330,1370, 380,1370, 380,520, 380,1370, 380,1370, 380,520, 380,520, 380,1370, 330,570, 380,520, 380,1370, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,1370, 330,570, 380,520, 380,520, 380,1370, 330,570, 380,520, 380,1320, 380,570, 330,570, 380,1370, 330,1370, 380,570, 330,570, 330,570, 330,570, 330,570, 380,520, 380,1320, 380,570, 380,1320, 380,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,570, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,520, 380,570, 330,570, 330,570, 330,520, 430,1320, 380,520, 380,570, 380,470, 430,470, 430,520, 380,520, 380,1320, 380},
    {3480,1670, 430,1270, 480,1270, 480,420, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,1270, 480,1270, 480,420, 480,1270, 430,470, 480,420, 480,1270, 430,1270, 480,470, 430,1270, 480,1270, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,1270, 480,1270, 430,470, 430,470, 430,470, 480,420, 480,420, 480,420, 480,420, 480,420, 480,1270, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,420, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,420, 480,420, 480,420, 480,420, 480,470, 430,470, 430,470, 430,470, 480,420, 480,420, 480,1270, 480},
    {3280,1820, 280,1470, 280,1420, 280,670, 280,620, 280,620, 280,1470, 280,620, 280,620, 280,1470, 280,1420, 280,670, 230,1470, 280,670, 230,620, 280,1470, 280,1470, 280,620, 280,1470, 280,1420, 280,670, 230,670, 280,1420, 280,670, 230,670, 280,1420, 280,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,670, 230,620, 280,670, 230,670, 230,620, 280,670, 230,670, 230,1470, 280,670, 230,670, 230,670, 280,1420, 280,670, 230,670, 230,1470, 280,620, 280,670, 230,1470, 280,1470, 280,670, 230,620, 280,670, 230,620, 280,670, 230,670, 280,1420, 280,1470, 280,620, 280,620, 280,620, 280,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,620, 280,670, 230,620, 280,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,670, 230,620, 280,670, 230,620, 280,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,670, 230,1470, 280,1470, 280,1470, 280,1420, 280,1470, 280,1470, 280,1470, 280,620, 280},
    {3280,1820, 380,1370, 330,1420, 280,620, 330,570, 330,570, 330,1420, 280,620, 280,670, 280,1420, 280,1470, 230,670, 330,1370, 280,670, 330,570, 330,1370, 380,1370, 330,620, 280,1420, 280,1470, 330,570, 330,570, 330,1420, 330,570, 330,570, 330,1370, 380,570, 330,570, 330,570, 280,620, 280,670, 280,570, 280,670, 280,620, 330,570, 230,670, 330,570, 330,570, 280,620, 280,1420, 280,670, 330,570, 280,620, 330,1420, 230,670, 280,620, 330,1370, 280,670, 330,570, 330,1370, 280,1470, 280,670, 330,520, 280,670, 330,570, 330,570, 280,620, 280,620, 330,1420, 280,620, 280,620, 280,620, 280,670, 230,670, 230,620, 280,670, 230,620, 280,670, 330,570, 330,570, 280,620, 330,570, 280,620, 330,570, 280,670, 280,570, 280,670, 230,670, 330,570, 230,670, 280,620, 330,570, 330,570, 330,570, 280,620, 280,670, 280,570, 280,670, 230,670, 230,670, 330,570, 280,620, 280,620, 280,620, 330,620, 230,670, 280,570, 280,670, 230,620, 280,670, 330,570, 330,570, 280,620, 280,620, 280,670, 280,570, 280,1470, 280,1470, 280,1420, 280,1470, 280,1470, 280,1420, 380,570, 280},
    {3280,1820, 380,1370, 330,1420, 330,570, 330,570, 330,620, 280,1420, 330,570, 330,620, 280,1420, 330,1420, 330,570, 330,1370, 380,570, 330,570, 330,1370, 280,1470, 330,620, 330,1370, 330,1420, 330,570, 330,570, 330,1420, 330,570, 330,570, 330,1420, 330,570, 330,570, 330,570, 330,570, 330,620, 280,570, 280,670, 230,670, 330,570, 330,570, 330,570, 330,570, 330,570, 280,1470, 230,670, 280,620, 330,570, 330,1420, 280,620, 280,620, 330,1370, 380,570, 330,570, 330,1420, 230,1470, 280,670, 330,520, 280,670, 330,570, 280,620, 330,570, 280,1470, 330,570, 280,620, 330,570, 280,620, 330,620, 280,570, 280,670, 330,570, 330,570, 230,670, 330,570, 280,620, 330,570, 280,620, 280,670, 280,620, 230,620, 280,670, 230,670, 330,570, 230,670, 230,670, 280,620, 280,620, 330,570, 280,620, 280,620, 280,670, 230,620, 280,620, 280,670, 330,570, 280,620, 280,620, 280,620, 280,620, 280,670, 230,620, 280,670, 230,620, 280,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,620, 280,1470, 280,620, 280,1470, 280,1420, 280,1470, 280,1470, 280,1470, 280,620, 280},
    {3330,1820, 230,1470, 280,1470, 280,670, 280,620, 280,620, 330,1370, 280,670, 230,670, 230,1470, 280,1470, 280,620, 330,1420, 230,670, 330,570, 330,1370, 280,1470, 280,670, 230,1470, 280,1470, 280,620, 280,670, 230,1470, 280,620, 330,570, 280,1470, 280,620, 280,620, 280,670, 230,670, 230,670, 230,620, 280,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,670, 230,1470, 280,620, 280,620, 280,670, 230,1470, 280,620, 280,670, 230,1470, 280,620, 280,620, 280,1470, 280,1420, 280,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,670, 230,620, 280,620, 280,670, 230,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,670, 230,620, 280,670, 230,620, 280,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,620, 280,670, 230,620, 280,670, 230,670, 230,670, 230,670, 280,620, 280,620, 280,620, 280,670, 230,620, 280,620, 280,620, 280,620, 280,670, 230,670, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,620, 280,670, 280,620, 280,620, 280,1470, 230,1470, 280,1470, 280,1470, 280,1420, 280,670, 280}
};

void sendIrCommand(int command) {
    
    // Check the command is in the command list.
    if (command >= POWEROFF && command <= ROTATIONAUTO || command >= TEMPERTURE16 && command <= TEMPERTURE31) {
        IrSender.sendRaw_P(rawIrData[command], sizeof(rawIrData[command]) / sizeof(rawIrData[command][0]), NEC_KHZ);
        if (command <= ROTATIONAUTO) {
            LOG1("%s command sent!\n", commandName[command]);
        }
        else {
            command -= 8;
            LOG1("%s command sent!\n", commandName[command]);
        }
    }
    else {
        LOG0("IR Command Error!\n");
    }
}

#endif // COOLERDATA_H