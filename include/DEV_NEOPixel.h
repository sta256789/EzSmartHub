#ifndef ESP32_EZSTARTKIT_V2_DEV_NEOPIXEL_H
#define ESP32_EZSTARTKIT_V2_DEV_NEOPIXEL_H

#ifdef EZSTARTKIT_WIRE_H
#define PIN EZSTARTKIT_IO16
#define NUMPIXELS EZSTARTKIT_PIXELSIZE
#else
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN -1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS -1
#endif

#include <Adafruit_NeoPixel.h>

static uint32_t HSVtoRGB(float H, float S,float V) {    
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if(H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if(H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if(H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if(H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if(H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }
    int R = (r + m) * 255;
    int G = (g +m ) * 255;
    int B = (b + m) * 255;
    return ((uint32_t)R << 16) | ((uint32_t)G << 8) | B;
}

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

struct NeoPixel_RGB : Service::LightBulb {

    Characteristic::On power{0, true};
    Characteristic::Hue H{0, true};
    Characteristic::Saturation S{0, true};
    Characteristic::Brightness B{50, true};
    Pixel *pixel;
    uint8_t nPixels;
    
    NeoPixel_RGB(uint8_t nPixels) : Service::LightBulb(){
  
      pixels.begin();                           // INITIALIZE NeoPixel strip object (REQUIRED)
      pixels.clear();                           // Set all pixel colors to 'off'
      B.setRange(5, 100, 5);                    // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 5%    
      this->nPixels = nPixels;                  // save number of Pixels in this LED Strand
      update();                                 // manually call update() to set pixel with restored initial values
    }
  
    boolean update() override {
      
      int powerState = power.getNewVal();
      
      float hue = H.getNewVal<float>();              // range = [0,360]
      float saturation = S.getNewVal<float>();       // range = [0,100]
      float brightness = B.getNewVal<float>();       // range = [0,100]
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(nPixels, HSVtoRGB(hue * powerState, saturation * powerState, brightness * powerState));
  
      // pixels.setPixelColor(nPixels, pixels.gamma32(pixels.ColorHSV(h*p, s*p, v*p)));
      // Serial.printf("p:%d ", p);
      // Serial.printf("h:%f ", h);
      // Serial.printf("s:%f ", s);
      // Serial.printf("v:%f ", v);
      // Serial.println(HSVtoRGB(h*p, s*p, v*p), BIN);
      // Serial.println(pixels.gamma32((pixels.ColorHSV(h*p, s*p, v*p))), BIN);
      LOG1("Power: %d Hue: %.1f Saturation: %.1f Brightness: %.1f\n", powerState, hue, saturation, brightness);
  
      pixels.show();   // Send the updated pixel colors to the hardware.
            
      return(true);  
    }
  };

#endif //ESP32_EZSTARTKIT_V2_DEV_NEOPIXEL_H