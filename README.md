**EzSmartHub**
===

![main page](https://github.com/sta256789/EzSmartHub/blob/main/snapshots/main%20page.jpeg?raw=true)  
Main page

![Overview](https://github.com/sta256789/EzSmartHub/blob/main/snapshots/overview.jpeg?raw=true)  
Overview

## **Introduction**
A smart home project using the ESP32 DevKit and EZ Start Kit+ expansion board, powered by the HomeSpan library. This device integrates multiple HomeKit functionalities such as temperature and humidity sensors, a relay-controlled LED light, an IR-based controller for air conditioner, and NeoPixel RGB lighting.



## **Features**
- **Clock Display**: Displays the current time, calendar, weather and the indoor temperature/relative humidity on a 1.3-inch OLED screen.
- **Temperature and Humidity Monitoring**: Uses sensors to monitor environmental conditions and displays data via HomeKit.
- **Relay-Controlled Light**: Allows control of an LED light connected via a relay module.
- **Cooler Controller**: Sends infrared signals to control an air conditioner.
- **NeoPixel RGB Lighting**: Supports dynamic RGB lighting effects using WS2812B LEDs.



## **Hardware Requirements**
1. **ESP32 DevKit** (e.g., ESP32-WROOM-32)
2. **EZ Start Kit+ Expansion Board** or you can wire the following devices by yourself
    - **DHT11 Sensor** (for temperature and humidity monitoring)
    - **Relay Module** (to control the LED light)
    - **NeoPixel LED Strip** (WS2812B)
    - **1.3-inch OLED Display** (SSD1306)
3. **IR Transmitter 3W** (for AC control)
4. **Module DC-DC Boost HW-105 5V 600mA**
5. **USB LED Light**



## **Software Requirements**
1. VS Code with PlatformIO and Arudino framework or Arduino IDE.
2. Libraries:
   - [HomeSpan](https://github.com/HomeSpan/HomeSpan) for HomeKit integration      
   - [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel) for RGB LED control
   - [Arduino IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) for infrared signal transmission
   - [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library) for temperature and humidity monitoring
        - [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor) required
   - [OpenWeatherOneCall v4.0.3](https://github.com/JHershey69/OpenWeatherOneCall) for current weather
        - [ArduinoJson](https://github.com/bblanchon/ArduinoJson) required
    - [u8g2](https://github.com/olikraus/u8g2) for OLED display handling



## **Setup Instructions**

### 1. Hardware Connections
| Component         | EZ Start Kit+ Pin | GPIO No. | Notes                            |
|-------------------|-------------------|----------|----------------------------------|
| Built-in Button   | -                 | 0        | Used for HomeSpan control        |
| Button B          | IO15              | 36       | Used for turning the OLED on/off |
| DHT11 Sensor      | IO7               | 15       | Data pin                         |
| LED (Green)       | IO6               | 13       | Used for HomeSpan status         |
| IR Transmitter    | IO5               | 12       | Sends IR signals for AC control  |
| NeoPixel LED Strip| IO16              | 26       | Data pin for RGB lighting        | 
| OLED (SCL)        | IO17              | 22       | I2C of the OLED screen           |
| OLED (SDA)        | IO18              | 21       | I2C of the OLED screen           |
| Relay Module      | IO13              | 25       | Controls the LED light           |

### 2. Install Required Libraries (Only for Arduino IDE)
Install the following libraries in Arduino IDE:
- HomeSpan
- Adafruit NeoPixel
- DHT Sensor Library
- IRremote
- OpenWeatherOneCall
- u8g2

### 3. Upload the Code
1. Clone this repository or download the project files.
2. Open `main.cpp` in VS Code or Arduino IDE.
3. Upload the code to your ESP32 board.



## **Usage**
1. Pair the device with Apple HomeKit using the setup code (466-37-726 by default) or scan the QR code displayed on the OLED screen.
2. Control features through Apple's Home app:
   - View real-time temperature and humidity data.
   - Toggle the relay-controlled light on or off.
   - Adjust AC settings via IR commands.
   - Change NeoPixel lighting effects.



## **Future Improvements**
- Add more weather information and weather forecast on the OLED screen.
- Add more AC status on the OLED screen.
- Implement a Tomato Clock.



## **Project Structure**
```
EzSmartHub/
├── include/ # Header files for various modules
│ ├── EzStartKit_Wire.h # EZ Start Kit+ wiring definitions
│ ├── DEV_DHT_Sensor.h # Temperature and humidity sensor module
│ ├── DEV_Relay.h # Relay control module
│ ├── DEV_NeoPixel.h # NeoPixel RGB LED module
│ ├── DEV_Cooler.h # IR-based cooler (AC) controller module
│ ├── DEV_OLED.h # OLED display module
│ └── README.md
├── lib/
│ └── README.md
├── snapshots/
│ ├── main page.jpeg
│ └── overview.jpeg
├── src/
│ ├── main.cpp # Main application code
│ └── README.md
├── test/
│ └── README.md
├── .gitignore
├── LICENSE
├── platformio.ini
└── README.md
```

## **Demo**
[Demo](https://github.com/sta256789/EzSmartHub)



## **Component Snapshots**
![Circus EZ Start Kit+](https://shoplineimg.com/6486dbe2afaddb00694ea79f/64e211c62033b000013f5963/2000x.webp?source_format=jpg)  

Circus EZ Start Kit+ from [iCShop](https://www.icshop.com.tw/products/368030200655?locale=en)

![IR Transmitter](https://img.alicdn.com/imgextra/i4/663392629/TB2IEgcf93PL1JjSZFxXXcBBVXa_!!663392629.jpg)  

High power(3W) IR Transmitter from [ebay](https://www.ebay.com/itm/264664170125)

![HW-105](https://m.media-amazon.com/images/I/31SyhtsJz1L.jpg)  

DC-DC Boost 5v 600ma Output from [Amazon](https://www.amazon.in/Hw-105-Dc-Dc-Boost-600ma-Output/dp/B08TVS57FG)

![USB LED Light](https://m.media-amazon.com/images/I/613YFv58lUL.jpg)  

Portable Mini USB Led Lamp Light from [Amazon](https://www.amazon.com/iMBPrice®-Portable-Flexible-Adjust-Laptop/dp/B011M59MW8)
