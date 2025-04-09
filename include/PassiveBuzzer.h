#ifndef PASSIVEBUZZER_H
#define PASSIVEBUZZER_H

#include "PitchesData.h"

#define BUZZER_PIN EZSTARTKIT_IO0
#define BUZZER_FREQ 5000  // Frequency (Hz)
#define BUZZER_RESOLUTION 8  // Resolution (8-bit)

// DoMiSoMiSo
const int setCompletedMelody[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_G5};
const int setCompletedDuration[] = {100, 100, 100, 100, 200};

// DoMiSo
const int taskEndingMelody[] = {NOTE_C5, NOTE_E5, NOTE_G5};
const int taskEndingDuration[] = {200, 200, 200};

// SoMiDo
const int breakEndingMelody[] = {NOTE_G5, NOTE_E5, NOTE_C5};
const int breakEndingDuration[] = {200, 200, 200};

void buzzerInitialize() {
    
    // Attach the buzzer pin to a PWM channel with a base frequency of 5kHz and 8-bit resolution
    LOG0(ledcAttach(BUZZER_PIN, BUZZER_FREQ, BUZZER_RESOLUTION) ? "Buzzer configuration is succeessful!\n" : "Buzzer configuration is failed!\n");
}

template <typename T, size_t N>

void ringBuzzer(const T (&melody)[N], const T (&duration)[N]) {
    
    uint32_t time_now = millis();
    
    for (int i = 0; i < N; i++) {
        
        // Play the bell sound at the specified frequency (C5)
        ledcWriteTone(BUZZER_PIN, melody[i]);
        
        // Set the volume (duty cycle) to 200 out of a maximum of 255
        ledcWrite(BUZZER_PIN, 200);
        
        while (millis() - time_now < duration[i]);
        time_now = millis();

        // Stop the sound by setting the frequency to zero
        ledcWrite(BUZZER_PIN, 0);        
    }
}


#endif